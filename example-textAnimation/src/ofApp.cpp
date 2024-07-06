#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    // 1. Load font
    textBlock.init("/Users/alptugan/oF/assets/fonts/OverpassMono-Regular.ttf", 18);
    
    // 2. Set Text
    textBlock.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    
    // 3. (Optional) You can set custom line height
    //textBlock.setLineHeight(38);
    
    // 4. Set box width to fit text into
    textBlock.wrapTextX(500);
    
    // 5. (Optional) Set color for the text
    textBlock.setColor(ofColor(200));
    
    // 6. Enable Animation (ofxTweenzor ois bundled with the addon, you do not need to import ofxTweenzor during project generation)
    textBlock.enableAnimatedText();
    
    // 7. Fade out animation after the app window created
    // Animation duration = 1.5,
    // Delay at start = 2,
    // Speed of word animation (Play around to get how it works intuitively) = 4
    // Type of animation = "fadeout"
    textBlock.animateText(1.5, 1, 4, "fadeout");
    
    // Set window position
    ofSetWindowPosition(0,0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int x = ofGetWidth() * 0.5 - textBlock.getWidth() * 0.5;
    int y = ofGetHeight() * 0.5 - textBlock.getHeight() * 0.5;
    ofBackground(10);
    
    
    // Draw Textblock
    // --------------------------------------------------
    textBlock.drawCenter(x, y);
    // --------------------------------------------------
    
    // Display bounding box
    // --------------------------------------------------
    ofSetColor(200, 0, 0);
    ofNoFill();
    ofDrawRectangle(textBlock.getBoundingBox());
    // --------------------------------------------------
    
    // Info
    ofDrawBitmapStringHighlight("Press The Following Keys\ni: Fade-in animation\no: Fade-out animation", 20,20);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'i') {
        // void animateText(float time = 1.0, float _delay = 0.0, float _delayRate = 0.2, string _type = "fadein");
        textBlock.animateText(1, 0, 0.4, "fadein");
    } else if(key == 'o') {
        textBlock.animateText(1, 0, 0.4, "fadeout");
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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
