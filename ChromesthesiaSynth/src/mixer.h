#pragma once
#include "ofMain.h"
#include "ofxStk.h"
#include "track.h"

using namespace stk;

class Mixer

{
public:
	Mixer();
	~Mixer();
	static void Write(vector<Track> tracks);
	static void Play(char* file, vector<Track> tracks);
};