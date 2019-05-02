#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	TrackGui track1;
	TrackGui track2;
	TrackGui track3;
	TrackGui track4;
	tracks.push_back(track1);
	tracks.push_back(track2);
	tracks.push_back(track3);
	tracks.push_back(track4);

	int xPos = 0;
	for (int i = 0; i < tracks.size(); i++) {
		tracks[i].gui = new ofxDatGui(xPos, kGuiSizeConst);
		tracks[i].gui->addHeader("Track " + to_string(i + 1));
		tracks[i].gui->getHeader()->setDraggable(false);

		tracks[i].image_button = tracks[i].gui->addButton("Select Image");
		tracks[i].image_button->onButtonEvent(this, &ofApp::onButtonEvent);

		tracks[i].instrument_dd = tracks[i].gui->addDropdown("Select an instrument", instrument_options);
		tracks[i].data_dd = tracks[i].gui->addDropdown("Select a Data Type", data_options);
		tracks[i].order_dd = tracks[i].gui->addDropdown("Select an Order Type", order_options);
		

		tracks[i].volume_slider = tracks[i].gui->addSlider("Volume", 0.00, 100.00);
		tracks[i].volume_slider->onSliderEvent(this, &ofApp::onSliderEvent);

		tracks[i].clear_button = tracks[i].gui->addButton("Clear Track");
		tracks[i].clear_button->onButtonEvent(this, &ofApp::onButtonEvent);

		tracks[i].track = new Track();

		xPos += kGuiSizeConst;
	}

	play_gui = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_RIGHT);
	play_button = play_gui->addButton("Play");
	play_button->onButtonEvent(this, &ofApp::onButtonEvent);

	ofxDatGui* exit_gui = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	exit_button = exit_gui->addButton("Exit");
	exit_button->onButtonEvent(this, &ofApp::onButtonEvent);

	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < tracks.size(); i++) {
		if (tracks[i].track->HasImage()) {
			ofImage copy(tracks[i].track_image);
			copy.resize(kGuiSizeConst, kGuiSizeConst);
			copy.draw(kGuiSizeConst * i, 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

	for (int i = 0; i < tracks.size(); i++) {
		if (e.target == tracks[i].image_button) {
			if (SelectImage(tracks[i].track_image)) {
				tracks[i].track->SetImage(tracks[i].track_image);
			}
		}

		if (e.target == tracks[i].clear_button) {
			tracks[i].data_dd->select(0);
			tracks[i].order_dd->select(0);
			tracks[i].instrument_dd->select(0);
			tracks[i].track->ClearTrack();
		}
	}

	if (e.target == play_button) {
		vector<Track> track_vec(tracks.size());

		bool filled_track = false;

		for (int i = 0; i < tracks.size(); i++) {
			DataExtracter::PixelData data_type = static_cast<DataExtracter::PixelData>(tracks[i].data_dd->getSelected()->getIndex());
			DataExtracter::PixelOrder order_type = static_cast<DataExtracter::PixelOrder>(tracks[i].order_dd->getSelected()->getIndex());
			Track::Instruments instrument = static_cast<Track::Instruments>(tracks[i].instrument_dd->getSelected()->getIndex());
			tracks[i].track->p_data_type = data_type;
			tracks[i].track->p_order_type = order_type;
			tracks[i].track->SetInstrument(instrument);
			track_vec[i] = *tracks[i].track;
			
			// check if there is a completed track
			if (tracks[i].track->HasImage()
				&& data_type != DataExtracter::PixelData::NonePD
				&& order_type != DataExtracter::PixelOrder::NonePO
				&& instrument != Track::Instruments::NoneInst) {
				filled_track = true;
			}
		}

		// if there is a completed track, write & play
		if (filled_track) {
			Mixer::Write(track_vec);
			Mixer::Play("voicer.ski", track_vec);
		}
	}

	if (e.target == exit_button) {
		OF_EXIT_APP(0);
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
				return true;
			}
			else {
				ofSystemAlertDialog("error: not a .jpg or .png file");
			}
		}
	}

	return false;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	for (int i = 0; i < tracks.size(); i++) {
		if (e.target == tracks[i].volume_slider) {
			tracks[i].track->SetVolume(e.value);
		}
	}
}


