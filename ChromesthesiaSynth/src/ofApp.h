#pragma once

#include "ofMain.h"
#include "ofxStk.h"
#include "ofxDatGui.h"
#include "data_extracter.h"
#include <iostream>
#include "track.h"
#include "mixer.h"

using namespace stk;

class ofApp : public ofBaseApp {

private: 	
	vector<string> data_options = { "Red", "Green", "Blue", "Lightness", "Hue", "Saturation", "Brightness" };
	vector<string> order_options = { "Left-Right", "Top-Bottom", "Random" };
	vector<string> instrument_options = { "none", "Bee Three", "Blow Bottle", "Blow Hole", "Bowed", "Clarinet", "Mandolin", "Percussion Flute", "Plucked", "Rhodey", "Saxofony", "Shaker", "Simple", "Sitar", "Tube Bell", "Whistle", "Wurley", "Test" };

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

	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onToggleEvent(ofxDatGuiToggleEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);

	bool SelectImage(ofImage &image);

	Track track;
	bool draw_image = false;
	int data_type = -1;
	int order_type = -1;
	int instrument_type = -1;

	ofImage image;
	ofxDatGui* gui;
	ofxDatGuiDropdown* data_dropdown;
	ofxDatGuiDropdown* order_dropdown;
	ofxDatGuiDropdown* instrument_dropdown;
	ofxDatGuiButton* image_button;
	ofxDatGuiToggle* play_button;
	
	struct TrackGui {
		ofImage track_image;
		ofxDatGui* gui;
		ofxDatGuiButton* image_button;
		ofxDatGuiButton* clear_image_button;
		ofxDatGuiDropdown* data_dd;
		ofxDatGuiDropdown* order_dd;
		ofxDatGuiDropdown* instrument_dd;
		ofxDatGuiSlider* volume_slider;
		
		Track* track;
	};

	vector<TrackGui> tracks;
	vector<ofImage> image_copies;
};