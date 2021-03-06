#pragma once
#include "ofMain.h"
#include "ofxStk.h"
#include "data_extracter.h"

using namespace stk;

class Track
{
private:
	
	Instrmnt *instrument = nullptr;
	bool image_loaded = false;
	float volume = 50.00;
	
public:

	static int Remap(float original);
	DataExtracter::PixelData p_data_type;
	DataExtracter::PixelOrder p_order_type;

	Track();
	~Track();

	enum Instruments {NoneInst, BeeThreeInst, BlowBotlInst, BlowHoleInst, 
		BowedInst, ClarinetInst, MandolinInst, PercFlutInst, 
		PluckedInst, RhodeyInst, SaxofonyInst, ShakerInst, 
		SimpleInst, SitarInst, TubeBellInst, WhistleInst, 
		WurleyInst};

	ofImage image;
	bool SetImage(ofImage image);
	bool SetInstrument(Track::Instruments selected);
	Instrmnt* GetInstrument();
	bool HasImage();
	void ClearTrack();
	bool SetVolume(float volume);
	float GetVolume();

	vector<float> GetData();
};

