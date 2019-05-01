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

	image_copies.reserve(tracks.size());

	int xPos = 0;
	for (int i = 0; i < tracks.size(); i++) {
		tracks[i].gui = new ofxDatGui(xPos, 270);
		ofxDatGui* current_gui = tracks[i].gui;
		string header = "Track " + to_string(i + 1);
		current_gui->addHeader(header);
		tracks[i].image_button = current_gui->addButton("Select an image");
		tracks[i].image_button->onButtonEvent(this, &ofApp::onButtonEvent);
		tracks[i].clear_image_button = current_gui->addButton("Clear image");
		tracks[i].clear_image_button->onButtonEvent(this, &ofApp::onButtonEvent);
		tracks[i].data_dd = current_gui->addDropdown("Select a data type", data_options);
		tracks[i].order_dd = current_gui->addDropdown("Select an order type", order_options);
		tracks[i].instrument_dd = current_gui->addDropdown("Select an instrument", instrument_options);
		tracks[i].volume_slider = current_gui->addSlider("Volume", 0.00, 100.00);
		tracks[i].volume_slider->onSliderEvent(this, &ofApp::onSliderEvent);
		tracks[i].track = new Track();

		xPos += 270;
	}

	gui = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_RIGHT);
	/*
	gui->addHeader("this is a header");
	image_button = gui->addButton("Select an image");
	image_button->onButtonEvent(this, &ofApp::onButtonEvent);
	data_dropdown = gui->addDropdown("Select a data type", data_options);
	order_dropdown = gui->addDropdown("Select an order type", order_options);
	instrument_dropdown = gui->addDropdown("Select an instrument", instrument_options);
	*/
	play_button = gui->addToggle("Play");
	play_button->onToggleEvent(this, &ofApp::onToggleEvent);
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < tracks.size(); i++) {
		if (tracks[i].track->HasImage()) {
			ofImage copy(tracks[i].track_image);
			copy.resize(270, 270);
			copy.draw(270 * i, 0);
		}
	}
	if (draw_image) {
		image.draw(0, 0);
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
	//string button_hit = e.target->getLabel();
	if (e.target == image_button) {
		SelectImage(image);
	}

	for (int i = 0; i < tracks.size(); i++) {
		if (e.target == tracks[i].image_button) {
			if (SelectImage(tracks[i].track_image)) {
				tracks[i].track->SetImage(tracks[i].track_image);
			}
		}

		if (e.target == tracks[i].clear_image_button) {
			tracks[i].track->ClearImage();
		}
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

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	for (int i = 0; i < tracks.size(); i++) {
		if (e.target == tracks[i].volume_slider) {
			cout << "moving" << endl;
			tracks[i].track->SetVolume(e.value);
		}
	}
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->getLabel() == "Play") {
		if (e.checked == 1) {
			vector<Track> track_vec(tracks.size());


			for (int i = 0; i < tracks.size(); i++) {
				tracks[i].track->p_data_type = static_cast<DataExtracter::PixelData>(tracks[i].data_dd->getSelected()->getIndex());
				tracks[i].track->p_order_type = static_cast<DataExtracter::PixelOrder>(tracks[i].order_dd->getSelected()->getIndex());
				tracks[i].track->SetInstrument(static_cast<Track::Instruments>(tracks[i].instrument_dd->getSelected()->getIndex()));
				track_vec[i] = *tracks[i].track;
			}

			Mixer::Write(track_vec);
			Mixer::Play("voicer.ski", track_vec);

			/*
			track.p_data_type = static_cast<DataExtracter::PixelData>(data_dropdown->getSelected()->getIndex());
			track.p_order_type = static_cast<DataExtracter::PixelOrder>(order_dropdown->getSelected()->getIndex());
			instrument_type = instrument_dropdown->getSelected()->getIndex();
			if (draw_image) {
				track.SetImage(image);
				//track.WriteTrack(static_cast<DataExtracter::PixelData>(data_type), static_cast<DataExtracter::PixelOrder>(order_type));
				//track.WriteTrack();
				track.SetInstrument(static_cast<Track::Instruments>(instrument_type));
				tracks.push_back(track);

				Track test_track;

				test_track.p_data_type = DataExtracter::PixelData::Green;
				test_track.p_order_type = DataExtracter::PixelOrder::TB;
				test_track.SetImage(image);
				test_track.SetInstrument(Track::Instruments::MandolinInst);
				
				tracks.push_back(test_track);

				Mixer::Write(tracks);
				//track.Play("voicer.ski", static_cast<Track::Instruments>(instrument_type));
				Mixer::Play("voicer.ski", tracks);
			}
			*/
		}
	}
}


