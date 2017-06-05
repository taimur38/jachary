#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int ticks = 0;
		float modded_ticks = 0;
		int init_radius = 20;

		ofShader shaderProg;
		ofVboMesh dat_mesh;
		ofImage dat_tex;

		// controlled vars

		int count = 20000;
		int activeColorIndex = 0;
		int activeMeshIndex = 0;
		float yScaleMod = 1.6;
		float xScaleMod = 1.2;
		float zScaleMod = 1.0;
		float speedMod = 100.0;
		float radius = 30;
		int perturbation = 1;
		int xSpacing = 4;
		int ySpacing = 3;

		//end controlled vars

		ofBoxPrimitive bp;
		ofSpherePrimitive sp;
		ofCylinderPrimitive cp;
		ofConePrimitive coneP;

		vector<ofMesh> meshes;

		ofCamera cam;
		ofLight light;
		vector<ofVec3f> gridpoints;
		vector<ofSpherePrimitive> spheres;
		
#define num_colors 10

		ofVec4f colorsVec[num_colors] = {
			ofVec4f(216.0/255.0, 126.0/255.0, 66.0/255.0, 1.0),		// orange
			ofVec4f(236.0/255.0, 92.0/255.0, 68.0/255.0, 1.0),		// red
			ofVec4f(70.0/255.0, 134.0/255.0, 198.0/255.0, 1.0),		// light blue
			ofVec4f(217.0/255.0, 228.0/255.0, 170.0/255.0, 1.0),	// light yellow
			ofVec4f(237.0/255.0, 247.0/255.0, 86.0/255.0, 1.0),		// yellow
			ofVec4f(254.0/255.0, 166.0/255.0, 214.0/255.0, 1.0),	// pink
			ofVec4f(160.0/255.0, 203.0/255.0, 210.0/255.0, 1.0),	// soft blue
			ofVec4f(162.0/255.0, 215.0/255.0, 189.0/255.0, 1.0),	// soft green
			ofVec4f(247.0/255.0, 197.0/255.0, 200.0/255.0, 1.0),	// soft pink
			//ofVec4f(25.0/255.0, 41.0/255.0, 61.0/255.0, 1.0),		// navy blue
		};

		/*
			"216, 126, 66",		// orange,
			"24, 41, 61",		// navy blue
			"236, 92, 68",		// red,
			"70, 134, 198",		// light blue,
			"217, 228, 170",	// light yellow
			"237, 247, 86",		// yellow
			"254, 166, 214",	// pink,
			"160, 203, 210",	// soft blue,
			"162, 215, 189",	// soft green,
			"247, 197, 200"		// soft pink
		*/
};
