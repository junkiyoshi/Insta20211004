#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->font_size = 25;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"±", u8"²", u8"³", u8"´", u8"µ",
		u8"¶", u8"·", u8"¸", u8"¹", u8"º",
		u8"»", u8"¼", u8"½", u8"¾", u8"¿",
		u8"À", u8"Á", u8"Â", u8"Ã", u8"Ä",
		u8"Å", u8"Æ", u8"Ç", u8"È", u8"É",
		u8"Ê", u8"Ë", u8"Ì", u8"Í", u8"Î",
		u8"Ï", u8"Ð", u8"Ñ", u8"Ò", u8"Ó",
		u8"Ô", u8"Õ", u8"Ö",
		u8"×", u8"Ø", u8"Ù", u8"Ú", u8"Û",
		u8"Ü", u8"¦", u8"Ý",
	};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	int span = 1;
	for (int i = 0; i < 500; i++) {

		int x = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, -300, 300);
		int y = 0;
		y = ofRandom(150, 170);
		y *= ofRandom(1) < 0.5 ? 1 : -1;
		int z = ofRandom(-20, 20);

		auto location = glm::vec3(x, y, z);
		auto rotation_x = glm::rotate(glm::mat4(), (ofGetFrameNum() * span + x * span + 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
		location = glm::vec3(x, 0, 0) + glm::vec4(location, 0) * rotation_x;

		int rb = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 39, 239);
		ofSetColor(rb, 239, rb);

		ofPushMatrix();
		ofTranslate(location - glm::vec3(15, 15, 0));
		ofRotateZ(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());
		ofRotateY(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());
		ofRotateX(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());

		this->font.drawString(this->words[(int)ofRandom(this->words.size())], 0, 0);

		ofPopMatrix();
	}

	for (int i = 0; i < 500; i++) {

		int x = (int)ofRandom(12) * 50 - 250 + ofRandom(-5, 5);
		int y = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -170, 170);
		int z = ofRandom(-10, 10);

		auto location = glm::vec3(x, y, z);
		auto rotation_x = glm::rotate(glm::mat4(), (ofGetFrameNum() * span + x * span + 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
		location = glm::vec3(x, 0, 0) + glm::vec4(location, 0) * rotation_x;

		ofPushMatrix();
		ofTranslate(location - glm::vec3(15, 15, 0));
		ofRotateZ(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());
		ofRotateY(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());
		ofRotateX(ofRandom(360) + ofRandom(0.2, 1) * ofGetFrameNum());

		int rb = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 39, 239);
		ofSetColor(rb, 239, rb);

		this->font.drawString(this->words[(int)ofRandom(this->words.size())], 0, 0);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}