#pragma once
#include "ofMain.h"
#include "ofxStk.h"
#include "track.h"

using namespace stk;

class Mixer
	
{
	// note this divides the max volume by this number
	// i.e. 3 means 0-100 is now 0-33
	// this was done because some instruments are simply too loud
	// also c++ does not like const floats/doubles
	static const int kVolumeConst = 3;

	static const int kSecPerMin = 60;
	static const int kBPM = 120;

public:
	static void Write(vector<Track> tracks);
	static void Play(char* file, vector<Track> tracks);
};