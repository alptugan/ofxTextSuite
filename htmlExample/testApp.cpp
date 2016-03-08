#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0,0,0);

    myText.init("verdana.ttf", 40);

	myTextFormat.tagOpened = "<b>";
	myTextFormat.tagClosed = "<\/b>";
	myTextFormat.font = "frabk.ttf";
	myTextFormat.size = 40;
	myTextFormat.color=ofColor(0,125,125);
	myTextFormat.antiAliesed=true;
	
	myText.setFormat(myTextFormat);

    myText.setHtmlText("Welcome. <b>L</b> is for Left, while <b>R</b> is for Right. Center it up with <b>C</b>, or hit <b>J</b> to Justify.  Press <b>1</b> to wrap constrained on x, or <b>2</b> to fit type to the area.<br/><br/>Breaked two lines.");

	alignment = OF_TEXT_ALIGN_LEFT;

    //Initially wrap the text to the screen width
    myText.wrapTextX(ofGetWidth());

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofClear(0);
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
void testApp::keyPressed(int key){

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
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

