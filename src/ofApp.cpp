#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	
	//cam.initGrabber(640, 480);
    
    int camWidth = 640;
	int camHeight = 480;
    ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight);
	
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(1.0);
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.4);
	ps3eye.setBrightness(0.6);
	ps3eye.setContrast(1.0);
	ps3eye.setHue(0.5);
	
	ps3eye.setFlicker(0);
    ps3eye.setLed(0);
    
	tracker.setup();
}

void ofApp::update() {
	ps3eye.update();
	if(ps3eye.isFrameNew()) {
		tracker.update(toCv(ps3eye));
		position = tracker.getPosition();
		scale = tracker.getScale();
		orientation = tracker.getOrientation();
		rotationMatrix = tracker.getRotationMatrix();
	}
}

void ofApp::draw() {
	ofSetColor(255);
	ps3eye.draw(0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	if(tracker.getFound()) {
		ofSetLineWidth(1);
		tracker.draw();
		
		//easyCam.begin();
		ofSetupScreenOrtho(640, 480, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
		ofTranslate(640 / 2, 480 / 2);
		applyMatrix(rotationMatrix);
		ofScale(5,5,5);
		ofDrawAxis(scale);
		//tracker.getObjectMesh().drawWireframe();
		//easyCam.end();
	}
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}