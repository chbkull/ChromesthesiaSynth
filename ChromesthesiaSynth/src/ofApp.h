#pragma once

#include "ofMain.h"
#include "SineWave.h"
#include "RtWvOut.h"
#include "BeeThree.h"
#include "RtAudio.h"
#include <cstdlib>

#include <signal.h>
#include <utilities.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "SKINImsg.h"
#include "WvOut.h"
#include "Instrmnt.h"
#include "JCRev.h"
#include "Voicer.h"
#include "Skini.h"
#include "RtAudio.h"
#include "Messager.h"
using namespace stk;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	int rtsine();
	int beeThreePlay();

	bool draw_image = false;
	ofImage image;
};