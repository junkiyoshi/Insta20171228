#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->particle_count = 600;
	this->font.loadFont("Kazesawa-Bold.ttf", 450, true, false, true);

	this->moji_1 = '?';
	this->moji_2 = '@';
	this->progress = 0;

	this->create_particles(this->moji_1, this->moji_2);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->progress += 0.05;
	if (this->progress > 2) {
		this->progress = 0;
		this->moji_1 = this->moji_2;
		this->moji_2 = this->moji_1 + 1;
		this->create_particles(this->moji_1, this->moji_2);
	}

	for (int i = 0; i < this->particle_count; i++) {
		this->particles[i].set_progress(this->progress);
		this->particles[i].update();
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2 - this->font.stringWidth("W") / 2, ofGetHeight() / 2 + this->font.stringHeight("W") / 2);

	for (int i = 0; i < this->particle_count; i++) {
		this->particles[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::create_particles(char moji_1, char moji_2) {
	
	this->particles.clear();
	this->particles.shrink_to_fit();
	for (int i = 0; i < this->particle_count; i++) {
		this->particles.push_back(Particle());
	}

	ofTTFCharacter char_1_path = this->font.getCharacterAsPoints(moji_1);
	ofTTFCharacter char_2_path = this->font.getCharacterAsPoints(moji_2);
	vector<ofPolyline> outline_1 = char_1_path.getOutline();
	vector<ofPolyline> outline_2 = char_2_path.getOutline();

	int count_1 = this->particle_count / outline_1.size();
	int count_2 = this->particle_count / outline_2.size();


	int particle_index = 0;
	for (int outline_index = 0; outline_index < outline_1.size(); outline_index++) {
		outline_1[outline_index] = outline_1[outline_index].getResampledByCount(count_1);

		vector<ofPoint> vertices = outline_1[outline_index].getVertices();
		for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {
			this->particles[particle_index].set_point_1(vertices[vertices_index]);
			particle_index++;
		}
	}

	//particle_index = 0;
	for (int outline_index = 0; outline_index < outline_2.size(); outline_index++) {
		outline_2[outline_index] = outline_2[outline_index].getResampledByCount(count_2);

		vector<ofPoint> vertices = outline_2[outline_index].getVertices();
		for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {
			this->particles[particle_index].set_point_2(vertices[vertices_index]);		
			particle_index--;
		}
	}
}


//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
