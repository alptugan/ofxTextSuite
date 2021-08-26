#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    myText.init("frabk.ttf", 80);
    myText.setText("Welcome. L is for Left, while R is for Right. Center it up with C, or hit J to Justify.  Press 1 to wrap constrained on x, or 2 to fit type to the area.");

    //Initially wrap the text to the screen width
    myText.wrapTextX(ofGetWidth() * 0.8);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofRectangle bb_rect;
    
    switch (alignment) {
            
        case OF_TEXT_ALIGN_LEFT:
            bb_rect = myText.draw(10,10);
            break;
        case OF_TEXT_ALIGN_RIGHT:
            bb_rect = myText.drawRight(ofGetWidth()-10, 10);
            break;
        case OF_TEXT_ALIGN_CENTER:
            bb_rect = myText.drawCenter(ofGetWidth()/2,10);
            break;
        case OF_TEXT_ALIGN_JUSTIFIED:
            bb_rect = myText.drawJustified(10, 10, myText.getWidth());
            break;

            
    }
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofDrawRectangle(bb_rect);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {


        case '1':
            myText.wrapTextX(ofGetWidth() * 0.6);
            break;
        case '2':
            myText.wrapTextArea(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
            break;
        case 'l':
            alignment = OF_TEXT_ALIGN_LEFT;
            break;
        case 'r':
            alignment = OF_TEXT_ALIGN_RIGHT;
            break;
        case 'c':
            alignment = OF_TEXT_ALIGN_CENTER;
            break;
        case 'j':
            alignment = OF_TEXT_ALIGN_JUSTIFIED;

            break;


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
void ofApp::windowResized(int w, int h){

}

