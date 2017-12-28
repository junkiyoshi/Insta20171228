#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	Particle(ofVec3f point_1, ofVec3f point_2);

	void update();
	void draw();

	void set_point_1(ofVec3f point_1);
	void set_point_2(ofVec3f point_2);
	void set_progress(float value);

	ofVec3f get_location();
private:
	ofVec3f location;
	ofVec3f point_1;
	ofVec3f point_2;

	float progress;

	ofImage img;
};