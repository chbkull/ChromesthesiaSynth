#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxDatGui* gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (draw_image) {
		image.draw(0, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case 'd':
		std::cout << "test" << std::endl;
		break;
	case ' ':
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


