#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1920, 1080, OF_WINDOW);			// <-------- setup the GL context


	ofGLWindowSettings winSetting;

	winSetting.setGLVersion(3, 2);
	winSetting.width = 1920 * 4;
	winSetting.height = 1080 * 4;
	ofCreateWindow(winSetting);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
