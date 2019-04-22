#include "ofApp.h"
#include "ofxBaseGui.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (draw_image) {
		image.draw(0, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case 'a':
		rtsine();
		break;
	case 's':
		beeThreePlay();
		break;
	case 'd':
		std::cout << "test" << std::endl;
		break;
	case ' ':
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image");

		//Check if the user opened a file
		if (openFileResult.bSuccess) {

			ofLogVerbose("User selected a file");
			image.load(openFileResult.getPath());
			draw_image = true;
		}
		else {
			ofLogVerbose("User hit cancel");
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

int ofApp::rtsine()
{
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::showWarnings(true);
	int nFrames = 44100;
	SineWave sine;
	RtWvOut *dac = 0;
	try {
		// Define and open the default realtime output device for one-channel playback
		dac = new RtWvOut(1);
	}
	catch (StkError &) {
		std::exit(1);
	}
	sine.setFrequency(441.0);
	// Option 1: Use StkFrames
	/*
	StkFrames frames( nFrames, 1 );
	try {
	  dac->tick( sine.tick( frames ) );
	}
	catch ( StkError & ) {
	  goto cleanup;
	}
	*/
	// Option 2: Single-sample computations
	for (int i = 0; i < nFrames; i++) {
		try {
			dac->tick(sine.tick());
		}
		catch (StkError &) {
			goto cleanup;
		}
	}
cleanup:
	delete dac;
	return 0;
}


// The TickData structure holds all the class instances and data that
// are shared by the various processing functions.
struct TickData {
	Instrmnt *instrument;
	StkFloat frequency;
	StkFloat scaler;
	long counter;
	bool done;
	// Default constructor.
	TickData()
		: instrument(0), scaler(1.0), counter(0), done(false) {}
};
// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *userData)
{
	TickData *data = (TickData *)userData;
	register StkFloat *samples = (StkFloat *)outputBuffer;
	for (unsigned int i = 0; i < nBufferFrames; i++) {
		*samples++ = data->instrument->tick();
		if (++data->counter % 2000 == 0) {
			data->scaler += 0.025;
			data->instrument->setFrequency(data->frequency * data->scaler);
		}
	}
	if (data->counter > 80000)
		data->done = true;
	return 0;
}

int ofApp::beeThreePlay() {
	// Set the global sample rate and rawwave path before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::setRawwavePath("data/rawwaves");
	TickData data;
	RtAudio dac;
	// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try {
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&data);
	}
	catch (RtAudioError& error) {
		error.printMessage();
		goto cleanup;
	}
	try {
		// Define and load the BeeThree instrument
		data.instrument = new BeeThree();
	}
	catch (StkError &) {
		goto cleanup;
	}
	data.frequency = 220.0;
	data.instrument->noteOn(data.frequency, 0.5);
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
	delete data.instrument;
	return 0;
}

