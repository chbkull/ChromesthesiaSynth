#include "mixer.h"



Mixer::Mixer()
{
}


Mixer::~Mixer()
{
}

void Mixer::Write(vector<Track> tracks) {
	cout << "entered write" << endl;

	vector <vector<float>> track_data;
	vector<float> dummy;
	for (int i = 0; i < tracks.size(); i++) {
		if (tracks[i].HasImage()) {
			track_data.push_back(dummy);
			track_data[i] = tracks[i].GetData();
		}
	}

	cout << "data set" << endl;

	ofstream file;
	file.open("voicer.ski");
	file << "NoteOn 0.1 0 0 0.00" << endl;
	file << "NoteOff 0.4 0 0 0.00" << endl;
	for (int i = 0; i < track_data[0].size(); i++) {
		for (int track_num = 0; track_num < track_data.size(); track_num++) {
			if (track_data[track_num].size() > 0 && track_data[track_num][i] > 0) {
				cout << track_num << ": " << tracks[track_num].GetVolume() << endl;
				file << "NoteOn 0 " << track_num << " " << Track::Remap(track_data[track_num][i]) << " " << tracks[track_num].GetVolume() << endl;
			}
		}

		for (int track_num = 0; track_num < track_data.size(); track_num++) {
			if (track_data[track_num][i] > 0) {
				if (track_num == 0) {
					file << "NoteOff 0.5 " << track_num << " " << Track::Remap(track_data[track_num][i]) << " 64.00" << endl;
				}
				else {
					file << "NoteOff 0 " << track_num << " " << Track::Remap(track_data[track_num][i]) << " 64.00" << endl;
				}
			}
		}
	}

	file.close();
}

// The TickData structure holds all the class instances and data that
// are shared by the various processing functions.
struct TickData {
	Voicer voicer;
	Messager messager;
	Skini::Message message;
	int counter;
	bool haveMessage;
	bool done;
	// Default constructor.
	TickData()
		: counter(0), haveMessage(false), done(false) {}
};
#define DELTA_CONTROL_TICKS 64 // default sample frames between control input checks
// The processMessage() function encapsulates the handling of control
// messages.  It can be easily relocated within a program structure
// depending on the desired scheduling scheme.
void processMessage(TickData* data)
{
	register StkFloat value1 = data->message.floatValues[0];
	register StkFloat value2 = data->message.floatValues[1];
	switch (data->message.type) {
	case __SK_Exit_:
		data->done = true;
		return;
	case __SK_NoteOn_:
		if (value2 == 0.0) // velocity is zero ... really a NoteOff
			data->voicer.noteOff(value1, 64.0);
		else { // a NoteOn
			data->voicer.noteOn(value1, value2);
		}
		break;
	case __SK_NoteOff_:
		data->voicer.noteOff(value1, value2);
		break;
	case __SK_ControlChange_:
		data->voicer.controlChange((int)value1, value2);
		break;
	case __SK_AfterTouch_:
		data->voicer.controlChange(128, value1);
	case __SK_PitchChange_:
		data->voicer.setFrequency(value1);
		break;
	case __SK_PitchBend_:
		data->voicer.pitchBend(value1);
	} // end of switch
	data->haveMessage = false;
	return;
}
// This tick() function handles sample computation and scheduling of
// control updates.  It will be called automatically when the system
// needs a new buffer of audio samples.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	TickData *data = (TickData *)dataPointer;
	register StkFloat *samples = (StkFloat *)outputBuffer;
	int counter, nTicks = (int)nBufferFrames;
	while (nTicks > 0 && !data->done) {
		if (!data->haveMessage) {
			data->messager.popMessage(data->message);
			if (data->message.type > 0) {
				data->counter = (long)(data->message.time * Stk::sampleRate());
				data->haveMessage = true;
			}
			else
				data->counter = DELTA_CONTROL_TICKS;
		}
		counter = min(nTicks, data->counter);
		data->counter -= counter;
		for (int i = 0; i < counter; i++) {
			*samples++ = data->voicer.tick();
			nTicks--;
		}
		if (nTicks == 0) break;
		// Process control messages.
		if (data->haveMessage) processMessage(data);
	}
	return 0;
}

void Mixer::Play(char* file, vector<Track> tracks)
{
	// Set the global sample rate and rawwave path before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::setRawwavePath("data/rawwaves/");
	int i;
	TickData data;
	RtAudio dac;
	Instrmnt *instrument[4];
	for (i = 0; i < 3; i++) instrument[i] = 0;
	// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try {
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&data);
	}
	catch (RtAudioError &error) {
		error.printMessage();
		goto cleanup;
	}
	try {
		// Define and load the instruments
		for (i = 0; i < tracks.size(); i++) {
			instrument[i] = tracks[i].GetInstrument();
		}
			
	}
	catch (StkError &) {
		goto cleanup;
	}
	// "Add" the instruments to the voicer.
	for (i = 0; i < tracks.size(); i++)
		data.voicer.addInstrument(instrument[i]);
	if (data.messager.setScoreFile(file) == false)
		goto cleanup;
	try {
		dac.startStream();
	}
	catch (RtAudioError &error) {
		error.printMessage();
		goto cleanup;
	}
	// Block waiting until callback signals done.
	while (!data.done)
		Stk::sleep(100);

	// Shut down the callback and output stream.
	try {
		dac.closeStream();
	}
	catch (RtAudioError &error) {
		error.printMessage();
	}
cleanup:
	for (i = 0; i < 3; i++) delete instrument[i];
	return;
}
