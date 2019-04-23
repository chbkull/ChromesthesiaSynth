#pragma once
#include "ofMain.h"
#include "ofxStk.h"

using namespace stk;

class Track
{
private:
	int channel;
	ofImage image;
	Instrmnt *instrument;
public:
	Track(int channel);
	~Track();
	ofImage GetImage();
	bool SetImage(ofImage image);
	bool SetInstrument(Instrmnt *instrument);
	void Play();

};

