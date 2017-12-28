#include "Particle.h"

Particle::Particle() : Particle(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0)) {}

Particle::Particle(ofVec3f point_1, ofVec3f point_2) {
	this->point_1 = point_1;
	this->point_2 = point_2;
	this->location = this->point_1;
	this->progress = 0.f;
	
	int size = 200;
	int r = 55;
	int g = 100;
	int b = 180;

	this->img.allocate(size, size, OF_IMAGE_COLOR);
	unsigned char* pixels = this->img.getPixels().getData();

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			float distance = ((size / 2 - x) * (size / 2 - x) + (size / 2 - y) * (size / 2 - y)) / 50.f;
			if (distance == 0) { distance = 0.003; }

			int r_value = r / distance - 3;
			r_value = max(0, min(r_value, 255));

			int g_value = g / distance - 3;
			g_value = max(0, min(g_value, 255));

			int b_value = b / distance - 3;
			b_value = max(0, min(b_value, 255));

			pixels[x * 3 * size + y * 3 + 0] = r_value;
			pixels[x * 3 * size + y * 3 + 1] = g_value;
			pixels[x * 3 * size + y * 3 + 2] = b_value;
		}
	}

	this->img.update();
}

void Particle::update(){
	if (this->progress > 1) {
		this->progress = 1;
	}
	
	ofVec3f gap = this->point_2 - this->point_1;	
	gap = gap * this->progress;

	this->location = this->point_1 + gap;
}

void Particle::draw() {
	if (this->point_1 != ofVec3f(0, 0, 0) || this->point_2 != ofVec3f(0, 0, 0)) {
		this->img.draw(this->location - ofVec3f(100, 100));
	}
}

void Particle::set_point_1(ofVec3f point_1) {
	this->point_1 = point_1;
}

void Particle::set_point_2(ofVec3f point_2) {
	this->point_2 = point_2;
}

void Particle::set_progress(float value) {
	this->progress = value;
}

ofVec3f Particle::get_location() {
	return this->location;
}