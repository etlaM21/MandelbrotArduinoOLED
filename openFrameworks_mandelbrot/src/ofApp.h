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

		const static int SCREEN_WIDTH = 128;
		const static int SCREEN_HEIGHT = 64;

		double xMin = -2.0;
		double xMax = 2.0;
		double yMin = -1.0;
		double yMax = 1.0;
		
		int maxIterations = 1000;

		double map(double inputNum, double minInput, double maxInput, double minOutput, double maxOutput);

		// Zoom
		int num_frames = 50;
		int frame = 0;
};
