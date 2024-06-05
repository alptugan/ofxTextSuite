#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    textBlock.init("frabk.ttf", 12);
    textBlock.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    
    // Set textBlock width
    textBlockWidth = ofGetWidth() - 40;
    
    // Set position
    posX = 20;
    posY = 20;
    
    //Initially wrap the text to the screen width
    textBlock.wrapTextX(textBlockWidth);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0x1111111);
    switch (alignment) {

        case OF_TEXT_ALIGN_LEFT:
            textBlock.draw(posX, posY);
            break;
        case OF_TEXT_ALIGN_RIGHT:
            textBlock.drawRight(posX, posY);
            break;
        case OF_TEXT_ALIGN_CENTER:
            textBlock.drawCenter(posX, posY);
            break;
        case OF_TEXT_ALIGN_JUSTIFIED:
            textBlock.drawJustified(posX, posY, ofGetWidth() - 40);
            break;

    }
        
    // Bounding box for showing how origin point changes according to the ALIGNMENT
    boundingBox = ofRectangle(textBlock.getPos().x, textBlock.getPos().y, textBlock.getWidth(), textBlock.getHeight());
    ofPushStyle();
    ofNoFill();
    ofSetHexColor(0xee0000);
    ofDrawRectangle(textBlock.getBoundingBox());
    ofPopStyle();
    
    
    // Alignment Options
    stringstream str;
    str << "Hit `1` to set random width for the textBlock" << endl;
    str << "Hit `2` to set full width and height for the textBlock" << endl;
    str << "Hit `l` to set the alignment LEFT for the textBlock" << endl;
    str << "Hit `r` to set the alignment RIGHT for the textBlock" << endl;
    str << "Hit `c` to set the alignment CENTER for the textBlock" << endl;
    str << "Hit `j` to set the alignment JUSTIFIED for the textBlock" << endl;
    ofDrawBitmapStringHighlight(str.str(), 20, ofGetHeight() - 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case '1':
            textBlock.wrapTextX(ofRandom(100, ofGetWidth() - 40));
            break;
        case '2':
            textBlock.wrapTextArea(ofGetWidth() - 100, ofGetHeight() - 200);
            break;
        case 'l':
            posX = 20;
            posY = 20;
            alignment = OF_TEXT_ALIGN_LEFT;
            break;
        case 'r':
            posX = ofGetWidth() - 20;
            posY = 20;
            alignment = OF_TEXT_ALIGN_RIGHT;
            break;
        case 'c':
            alignment = OF_TEXT_ALIGN_CENTER;
            posX = ofGetWidth() * 0.5;
            posY = 20;
            break;
        case 'j':
            posX = 20;
            posY = 20;
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


