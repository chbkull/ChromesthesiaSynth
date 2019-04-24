#include "track.h"

Track::Track(int channel) {
	this->channel = channel;
}

Track::~Track()
{
}

ofImage Track::GetImage() {
	return image;
}

bool Track::SetImage(ofImage image) {
	return true;
}

bool Track::SetInstrument(Instrmnt *instrument) {
	return true;
}

void Track::Play() {
	ofPixels pixels = image.getPixels();
}