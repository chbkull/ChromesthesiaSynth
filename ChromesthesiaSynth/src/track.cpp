#include "track.h"


Track::Track() {
}

Track::~Track()
{
}

bool Track::SetVolume(float volume) {
	this->volume = volume;
	return true;
}

float Track::GetVolume() {
	return volume;
}

bool Track::SetImage(ofImage image) {
	this->image = image;
	image_loaded = true;
	return true;
}

bool Track::HasImage() {
	return image_loaded;
}

void Track::ClearTrack() {
	image.clear();
	image_loaded = false;
	instrument = nullptr;
	p_data_type = DataExtracter::PixelData::NonePD;
	p_order_type = DataExtracter::PixelOrder::NonePO;
}

bool Track::SetInstrument(Track::Instruments selected) {
	Stk::setRawwavePath("data/rawwaves/");
	
	try {
		switch (selected) {
			case Instruments::NoneInst: {
				instrument = nullptr;
				return true;
			}
			case Instruments::BeeThreeInst: {
				instrument = new BeeThree();
				return true;
			}
			case Instruments::BlowBotlInst: {
				instrument = new BlowBotl();
				return true;
			}
			case Instruments::BlowHoleInst: {
				instrument = new BlowHole(8.0);
				return true;
			}
			case Instruments::BowedInst: {
				instrument = new Bowed(8.0);
				return true;
			}
			case Instruments::ClarinetInst: {
				instrument = new Clarinet(8.0);
				return true;
			}
			case Instruments::MandolinInst: {
				instrument = new Mandolin(8.0);
				return true;
			}
			case Instruments::PercFlutInst: {
				instrument = new PercFlut();
				return true;
			}
			case Instruments::PluckedInst: {
				instrument = new Plucked(8.0);
				return true;
			}
			case Instruments::RhodeyInst: {
				instrument = new Rhodey();
				return true;
			}
			case Instruments::SaxofonyInst: {
				instrument = new Saxofony(8.0);
				return true;
			}
			case Instruments::ShakerInst: {
				instrument = new Shakers();
				return true;
			}
			case Instruments::SimpleInst: {
				instrument = new Simple();
				return true;
			}
			case Instruments::SitarInst: {
				instrument = new Sitar();
				return true;
			}
			case Instruments::TubeBellInst: {
				instrument = new TubeBell();
				return true;
			}
			case Instruments::WhistleInst: {
				instrument = new Whistle();
				return true;
			}
			case Instruments::WurleyInst: {
				instrument = new Wurley();
				return true;
			}
		}
	}
	catch (StkError &) {
		return false;
	}
}

Instrmnt* Track::GetInstrument() {
	return instrument;
}

vector<float> Track::GetData() {
	
	if (this->HasImage() && p_data_type != DataExtracter::PixelData::NonePD
		&& p_order_type != DataExtracter::PixelOrder::NonePO) {
		return DataExtracter::Extract(image, p_data_type, p_order_type);
	}
	else {
		vector<float> empty;
		return empty;
	}

	
}

int Track::Remap(float original) {
	int cScaleMod[7] = { 0, 2, 3, 5, 7, 8, 10};
	
	int low = 57;
	int high = 68;
	int diff = high - low;
	// remaps 0-255 to low-high
	int result = (int)floor(((diff * original) / 255) + low);
	// sets A to 0 (shifted by 9 on provided array) then mod 12s (12 half steps in octave)
	int mod = (result - 9) % 12;
	bool check = false;

	for (int i = 0; i < sizeof(cScaleMod); i++) {
		if (mod == cScaleMod[i]) {
			check = true;
			break;
		}
	}

	// if in scale return note, otherwise return note before it
	if (check) {
		return result;
	}
	else {
		return result - 1;
	}
}
