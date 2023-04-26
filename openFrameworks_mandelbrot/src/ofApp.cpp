#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            ofSetColor(0);
            double x0 = map(x, 0, SCREEN_WIDTH, xMin, xMax);
            double y0 = map(y, 0, SCREEN_HEIGHT, yMin, yMax);
            double x1 = 0.0;
            double y1 = 0.0;
            int iteration = 0;
            double z = x1 * x1 + y1 * y1;
            while (z <= 2.0 * 2.0 && iteration < maxIterations) {
                double xtemp = x1 * x1 - y1 * y1 + x0;
                y1 = 2 * x1 * y1 + y0;
                x1 = xtemp;
                z = x1 * x1 + y1 * y1;
                iteration++;
            }
            // cout << "z " << z;
            if (z < 2.0 * 2.0) {
                ofSetColor(255);
            }
            ofDrawRectangle(x, y, 1, 1);
        }
    }
    cout << "Frame " << frame << " done!\n";
    if (frame >= 0) {
        double xShift = -0.25;
        double yShift = +0.637618;
        xMin += xShift;
        xMax += xShift;
        yMin += yShift;
        yMax += yShift;
    }
    double scale = 0.5;
    xMin *= scale;
    xMax *= scale;
    yMin *= scale;
    yMax *= scale;

    maxIterations += 25;
    frame++;
    if (frame >= num_frames) {
        xMin = -2.0;
        xMax = 2.0;
        yMin = -1.0;
        yMax = 1.0;
        maxIterations = 1000;
        frame = 0;
    }
    ofSleepMillis(200);
    /* xMin = -2.0;
    xMax = 2.0;
    yMin = -1.0;
    yMax = 1.0; */
}

double ofApp::map(double inputNum, double minInput, double maxInput, double minOutput, double maxOutput) {
    return (inputNum - minInput) * (maxOutput - minOutput) / (maxInput - minInput) + minOutput;
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
