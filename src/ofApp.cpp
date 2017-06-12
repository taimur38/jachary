#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// create grid

	//ofSetWindowShape(1920 * 4, 1080);
	//ofSetFullscreen(true);
	ofBackground(0);
	light.setDiffuseColor(ofFloatColor(0.85, 0.85, 0.85));
	ofEnableDepthTest();
	ofEnableLighting();
	ofSetSphereResolution(48);
	ofSetSmoothLighting(true);
	//ofDisableAlphaBlending();

	ofSetLogLevel(OF_LOG_VERBOSE);

	sp.setRadius(init_radius);
	bp.set(init_radius);
	cp.set(float(init_radius), float(init_radius));
	coneP.set(init_radius, float(init_radius));

	//meshes.push_back(sp.getMesh());
	meshes.push_back(bp.getMesh());
	meshes.push_back(cp.getMesh());
	meshes.push_back(coneP.getMesh());

	dat_mesh = sp.getMesh();
	
	dat_texes.push_back(*new ofImage());
    dat_texes.push_back(*new ofImage());
    dat_texes.push_back(*new ofImage());
    
    dat_texes[0].load("jachary_blue.jpg");
    dat_texes[1].load("jachary_purple.jpg");
    dat_texes[2].load("jachary_red.jpg");

	shaderProg.load("shaders/instanced.vert", "shaders/instanced.frag");
	cam.setupPerspective(false, 60, 0, 10000);
	cam.setPosition(ofVec3f(0, 1920 / 4, 300));
    
    light.setDiffuseColor(ofColor(0.0, 255.0, 0.0));
    
    light.setPointLight();


	client = new WsClient("localhost:1337");

	client->on_message = [this](shared_ptr<WsClient::Message> message) {
		auto message_str = message->string();

		boomTick = ticks;

		ofLog(OF_LOG_VERBOSE, "" + message_str);

	};

	client->on_open = [this]() {
		ofLog(OF_LOG_VERBOSE, "connected");
		/*
		cout << "Client: Opened connection" << endl;

		string message = "Hello";
		cout << "Client: Sending message: \"" << message << "\"" << endl;

		auto send_stream = make_shared<WsClient::SendStream>();
		*send_stream << message;
		client->send(send_stream);
		*/
	};

	client->on_close = [](int status, const string& reason) {
		ofLog(OF_LOG_VERBOSE, "closed conn %d", status);
	};

	//See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
	client->on_error = [](const boost::system::error_code& ec) {
		//cout << "Client: Error: " << ec << ", error message: " << ec.message() << endl;
		ofLog(OF_LOG_VERBOSE, "client error");
	};

	client_thread = thread([this]() {
		client->start();
	});

	client_thread.detach();

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
    //dat_tex.getTexture().bind();
	shaderProg.begin();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);

	shaderProg.setUniform1i("count", count);
	shaderProg.setUniform4f("color1", colorsVec[activeColorIndex % num_colors]);
	shaderProg.setUniform4f("color2", colorsVec[(activeColorIndex+1) % num_colors]);
	shaderProg.setUniform1i("ticks", ticks);
	shaderProg.setUniform1i("perturbation", perturbation);
	shaderProg.setUniformTexture("tex0", dat_texes[activeColorIndex % 3].getTexture(), 0);
	shaderProg.setUniform1i("xSpacing", xSpacing);
	shaderProg.setUniform1i("ySpacing", ySpacing);
	shaderProg.setUniform1i("boomTick", boomTick);
	shaderProg.setUniform1i("boomDuration", boomDuration);
	shaderProg.setUniform1i("boomStrength", boomStrength);
    shaderProg.setUniform1f("timeValue", ofGetElapsedTimef());
    shaderProg.setUniform1f("waveTime", waveTime);
    shaderProg.setUniform1i("waveDuration", waveDuration);


	dat_mesh.drawInstanced(OF_MESH_FILL, count);

	glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);

	shaderProg.end();
    //dat_tex.getTexture().unbind();
	light.disable();
    //dat_tex.getTexture().draw(0, 0, 0);
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
    const int W = 119;

	const int ENTER = 13;

	if (key == ENTER) {
		boomTick = ticks;
	}
    
    if (key == W) {
        waveTime = ticks;
    }

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
