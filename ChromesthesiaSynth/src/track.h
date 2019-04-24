#pragma once
#include "ofMain.h"
#include "ofxStk.h"
#include "data_extracter.h"

using namespace stk;

class Track
{
private:
	int channel;
	ofImage image;
	Instrmnt *instrument;
	static int Remap(float original);
public:
	Track();
	~Track();

	ofImage GetImage();
	bool SetChannel(int channel);
	bool SetImage(ofImage image);
	bool SetInstrument(Instrmnt *instrument);

	void WriteTrack(DataExtracter::PixelData p_data, DataExtracter::PixelOrder p_order);
	void Play(char* file);

};

