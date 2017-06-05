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

	meshes.push_back(sp.getMesh());
	meshes.push_back(bp.getMesh());
	meshes.push_back(cp.getMesh());
	meshes.push_back(coneP.getMesh());

	dat_mesh = sp.getMesh();
	
	dat_tex.load("jachary_blue.jpg");

	shaderProg.load("shaders/instanced.vert", "shaders/instanced.frag");
	cam.setupPerspective(false, 60, 0, 10000);
	cam.setPosition(ofVec3f(0, 1920 / 4, 300));

}

//--------------------------------------------------------------
void ofApp::update() {

	modded_ticks = (modded_ticks + 1.0 / speedMod);
	ticks++;

	if (ticks % 1000 == 0) {
		activeMeshIndex = (activeMeshIndex + 1) % meshes.size();
	}

	if (ticks % 500 == 0)
		activeColorIndex++;


	cam.setPosition(ofVec3f(
		sin(modded_ticks * xScaleMod) * (1080/4),
		cos(modded_ticks * yScaleMod) * (1920/4),
		(sin(modded_ticks * zScaleMod) + 1)/2 * 1500 + 300 
	));

	dat_mesh = meshes.at(activeMeshIndex % meshes.size());

	cam.lookAt(ofVec3f(
		sin(modded_ticks),
		cos(modded_ticks),
		sin(modded_ticks)
	));


}

//--------------------------------------------------------------
void ofApp::draw() {

	//ofBackgroundGradient(ofColor(18, 33, 54), ofColor(18, 22, 28));

	ofBackground(ofColor::black);
	ofSetColor(ofColor::white);
	cam.begin();
	light.enable();
	shaderProg.begin();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shaderProg.setUniform1i("count", count);
	shaderProg.setUniform4f("color1", colorsVec[activeColorIndex % num_colors]);
	shaderProg.setUniform4f("color2", colorsVec[(activeColorIndex+1) % num_colors]);
	shaderProg.setUniform1i("ticks", ticks);
	shaderProg.setUniform1i("perturbation", perturbation);
	shaderProg.setUniformTexture("tex0", dat_tex.getTexture(), 0);
	shaderProg.setUniform1i("xSpacing", xSpacing);
	shaderProg.setUniform1i("ySpacing", ySpacing);

	dat_mesh.drawInstanced(OF_MESH_FILL, count);

	glDisable(GL_CULL_FACE);

	shaderProg.end();
	light.disable();
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	ofLog(OF_LOG_VERBOSE, "key pressed: %d", key);

	const int LEFT = 356;
	const int UP = 357;
	const int RIGHT = 358;
	const int DOWN = 359;

	const int SPACE = 32;
	const int Z = 122;

	if (key == SPACE) {
		activeColorIndex++;
	}

	if (key == Z) {
		activeMeshIndex++;
	}


	if (key >= 356 && key <= 359) {

		int step = 100;
		auto curr = cam.getPosition();
		switch (key) {
		case LEFT: 
			//cam.setPosition(ofVec3f(curr.x - step, curr.y, curr.z));
			xSpacing--;
			break;
		case UP:
			//cam.setPosition(ofVec3f(curr.x, curr.y, curr.z + step));
			ySpacing++;
			break;
		case RIGHT:
			//cam.setPosition(ofVec3f(curr.x + step, curr.y, curr.z));
			xSpacing++;
			break;
		case DOWN:
			//cam.setPosition(ofVec3f(curr.x, curr.y, curr.z - step));
			ySpacing--;
			break;
		}

	}
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