#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    myText.init("frabk.ttf", 80);
    myText.setText("Welcome. L is for Left, while R is for Right. Center it up with C, or hit J to Justify.  Press 1 to wrap constrained on x, or 2 to fit type to the area.");

    //Initially wrap the text to the screen width
    myText.wrapTextX(ofGetWidth());

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    switch (alignment) {

        case OF_TEXT_ALIGN_LEFT:
            myText.draw(0,0);
            break;
        case OF_TEXT_ALIGN_RIGHT:
            myText.drawRight(ofGetWidth(), 0);
            break;
        case OF_TEXT_ALIGN_CENTER:
            myText.drawCenter(ofGetWidth()/2,0);
            break;
        case OF_TEXT_ALIGN_JUSTIFIED:
            myText.drawJustified(0, 0, myText.getWidth());
            break;

    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {


        case '1':
            myText.wrapTextX(ofGetWidth());
            break;
        case '2':
            myText.wrapTextArea(ofGetWidth(), ofGetHeight());
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

