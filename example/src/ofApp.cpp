#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //image.load("anohito.jpg");
    video.load("fire.mp4");
    video.play();
    chromaKey.keyColor = ofColor(0, 255, 0); // set key color to green
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    cam.setDeviceID(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
    video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofBackgroundGradient(ofColor(128), ofColor(31), OF_GRADIENT_LINEAR);
    cam.draw(0,0);
    // set threshold by mouseX
    chromaKey.threshold = ofMap(mouseX, 0, ofGetWidth(), 0.0, 1.0);
    
    // draw chromaKey image
    chromaKey.begin();
    //image.draw(0, 0);
    video.draw(0,0);
    chromaKey.end();
    
    // draw threshold value
    ofDrawBitmapString("ChromaKey threshold = " + ofToString(chromaKey.threshold), 20, 20);
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
