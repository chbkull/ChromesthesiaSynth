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
	
public:

	static int Remap(float original);
	DataExtracter::PixelData p_data_type;
	DataExtracter::PixelOrder p_order_type;

	Track();
	~Track();

	enum Instruments {MandolinInst, PluckedInst, SimpleInst, TestInst};

	ofImage GetImage();
	bool SetChannel(int channel);
	bool SetImage(ofImage image);
	bool SetInstrument(Track::Instruments selected);
	Instrmnt* GetInstrument();

	//void WriteTrack(DataExtracter::PixelData p_data, DataExtracter::PixelOrder p_order);
	void WriteTrack();
	vector<float> GetData();

	void Play(char* file, Track::Instruments selected_instrument);

};

