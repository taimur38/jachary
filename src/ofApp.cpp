#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// create grid

	//ofSetWindowShape(1920 * 4, 1080);
	ofSetFullscreen(true);
	ofBackground(0);
	light.setDiffuseColor(ofFloatColor(0.85, 0.85, 0.85));
	ofEnableDepthTest();
	ofEnableLighting();
	ofSetSphereResolution(48);
	ofSetSmoothLighting(true);
	ofDisableAlphaBlending();

	ofSetLogLevel(OF_LOG_VERBOSE);

	sp.setRadius(init_radius);
	bp.set(init_radius);
	cp.set(float(init_radius) / 3.0, float(init_radius));
	coneP.set(init_radius, float(init_radius) / 3.0);

	dat_mesh = sp.getMesh();

	shaderProg.load("shaders/instanced.vert", "shaders/instanced.frag");
	cam.setupPerspective(false, 60, 0, 10000);

}

//--------------------------------------------------------------
void ofApp::update() {

	modded_ticks = (modded_ticks + 1.0 / speedMod);
	ticks++;

	if (ticks % 400 == 0) {
		dat_mesh = coneP.getMesh();
	}
	else if (ticks % 300 == 0) {
		dat_mesh = cp.getMesh();
	}
	else if (ticks % 200 == 0) {
		dat_mesh = sp.getMesh();
	}
	else if (ticks % 100 == 0) {
		dat_mesh = bp.getMesh();
	}

	cam.setPosition(ofVec3f(
		sin(modded_ticks * xScaleMod) * (1080/4),
		cos(modded_ticks * yScaleMod) * (1920/4),
		(sin(modded_ticks * zScaleMod) + 1)/2 * 1500 + 300 
	));

	cam.lookAt(ofVec3f(
		sin(modded_ticks),
		cos(modded_ticks),
		sin(modded_ticks)
	));


}

//--------------------------------------------------------------
void ofApp::draw() {

	//ofBackgroundGradient(ofColor(18, 33, 54), ofColor(18, 22, 28));

	int count = 20000;
	ofBackground(ofColor::black);
	ofSetColor(ofColor::white);
	cam.begin();
	light.enable();
	shaderProg.begin();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shaderProg.setUniform1i("count", count);

	//dat_mesh.drawInstanced(OF_MESH_FILL, (1080 / (3 * init_radius)) * (1920 / (4 * init_radius)));
	dat_mesh.drawInstanced(OF_MESH_FILL, count);

	glDisable(GL_CULL_FACE);

	shaderProg.end();
	light.disable();
	cam.end();

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
