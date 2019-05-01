#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	image_button = gui->addButton("Select an image");
	image_button->onButtonEvent(this, &ofApp::onButtonEvent);
	vector<string> data_options = { "Red", "Green", "Blue", "Lightness", "Hue", "Saturation", "Brightness" };
	data_dropdown = gui->addDropdown("Select a data type", data_options);
	vector<string> order_options = { "Left-Right", "Top-Bottom", "Random", "8x8" };
	order_dropdown = gui->addDropdown("Select an order type", order_options);
	vector<string> instrument_options = { "Mandolin", "Plucked", "Simple", "Test" };
	instrument_dropdown = gui->addDropdown("Select an instrument", instrument_options);
	play_button = gui->addToggle("Play");
	play_button->onToggleEvent(this, &ofApp::onToggleEvent);


	track.SetChannel(0);
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (draw_image) {
		image.draw(0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
		case 'd':
		{
			data_type = data_dropdown->getSelected()->getIndex();
			order_type = order_dropdown->getSelected()->getIndex();
			instrument_type = instrument_dropdown->getSelected()->getIndex();
			if (draw_image && data_type != -1 && order_type != -1) {
				track.SetImage(image);
				track.WriteTrack(static_cast<DataExtracter::PixelData>(data_type), static_cast<DataExtracter::PixelOrder>(order_type));
				track.Play("example.ski", static_cast<Track::Instruments>(instrument_type));
			}
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
	string button_hit = e.target->getLabel();
	if (button_hit == "Select an image") {
		SelectImage(image);
	}
}

bool ofApp::SelectImage(ofImage &image) {
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image");

	//Check if file successfully opened
	if (openFileResult.bSuccess) {
		ofFile file(openFileResult.getPath());
		if (file.exists()) {
			string fileExtension = ofToUpper(file.getExtension());
			if (fileExtension == "JPG" || fileExtension == "PNG") {
				image.load(openFileResult.getPath());
				draw_image = true;
				return true;
			}
			else {
				ofSystemAlertDialog("error: not a .jpg or .png file");
			}
		}
	}

	return false;
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->getLabel() == "Play") {
		if (e.checked == 1) {
			data_type = data_dropdown->getSelected()->getIndex();
			order_type = order_dropdown->getSelected()->getIndex();
			instrument_type = instrument_dropdown->getSelected()->getIndex();
			if (draw_image && data_type != -1 && order_type != -1) {
				track.SetImage(image);
				track.WriteTrack(static_cast<DataExtracter::PixelData>(data_type), static_cast<DataExtracter::PixelOrder>(order_type));
				track.Play("example.ski", static_cast<Track::Instruments>(instrument_type));
			}
		}
	}
}


