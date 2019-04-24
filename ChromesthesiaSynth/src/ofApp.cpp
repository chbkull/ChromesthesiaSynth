#include "ofApp.h"
#include "data_extracter.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	vector<string> options = { "Red", "Green", "Blue", "Lightness", "Hue", "Saturation", "Brightness" };
	data_dropdown = gui->addDropdown("Select an option", options);
	
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
			data_type = data_dropdown->getSelected()->getIndex();
			if (draw_image && data_type != -1) {
				std::vector<std::vector<float>> data = DataExtracter::Extract(image, static_cast<DataExtracter::PixelData>(data_type), DataExtracter::PixelOrder::LR);
				for (int x = 0; x < image.getWidth(); x++) {
					for (int y = 0; y < image.getHeight(); y++) {
						std::cout << data[x][y] << " ";
					}
					std::cout << std::endl;
				}
			}
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


