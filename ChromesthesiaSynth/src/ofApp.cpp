#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	vector<string> data_options = { "Red", "Green", "Blue", "Lightness", "Hue", "Saturation", "Brightness" };
	data_dropdown = gui->addDropdown("Select an option", data_options);
	vector<string> order_options = { "Left-Right", "Top-Bottom", "Random", "8x8" };
	order_dropdown = gui->addDropdown("Select an option", order_options);
	track.SetChannel(0);
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (draw_image) {
		image.draw(200, 200);
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
			if (draw_image && data_type != -1 && order_type != -1) {
				track.SetImage(image);
				track.WriteTrack(static_cast<DataExtracter::PixelData>(data_type), static_cast<DataExtracter::PixelOrder>(order_type));
			}
			break;
		}
		case ' ':
		{
			ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image");

			//Check if the user opened a file
			if (openFileResult.bSuccess) {

				ofLogVerbose("User selected a file");
				image.load(openFileResult.getPath());
				draw_image = true;
			}
			else {
				ofLogVerbose("User hit cancel");
			}
			break;
		}
		case 'p':
			track.Play("example.ski");
			break;
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


