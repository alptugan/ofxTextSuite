//
//  ofxTextSequencer.cpp
//
//  Created by Patricio González Vivo on 4/9/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#include "ofxTextSequencer.h"

ofxTextSequencer::ofxTextSequencer(){
    currentLine = 0;
    countDown   = 1.0;
    seconds     = 1.0;
    speed       = 1.0;
    bPlay       = false;
    bMessage    = false;
}

bool ofxTextSequencer::load(string _xmlFile){
    bool    success = false;
    
    ofxXmlSettings XML;
    
    if (XML.loadFile(_xmlFile)){
        string fontFile = XML.getValue("font", "helvetica.ttf");
        float fontSize = XML.getValue("fontSize", 30.0);
        secondsForChar = XML.getValue("secondForChar", 0.2);
        waitingTime = XML.getValue("waitingTime", 2.0);
        
        textBlock.loadFont( fontFile, fontSize);
        
        int totalLines = XML.getNumTags("phrase");
        
        for(int i = 0; i < totalLines; i++){
            XML.pushTag("phrase",i);
            ofxTextPhrase newPhrase;
            
            newPhrase.text = XML.getValue("text", "Text");
            newPhrase.seconds = newPhrase.text.length() * secondsForChar;
            newPhrase.speed = XML.getValue("speed", 1.0);
            
            subsChars(newPhrase.text);
            string alignment = XML.getValue("hAlign", "LEFT");
            
            if (alignment == "LEFT"){
                newPhrase.hAlign = OF_TEXT_ALIGN_LEFT;
            } else if ( alignment == "RIGHT"){
                newPhrase.hAlign = OF_TEXT_ALIGN_RIGHT;
            } else if ( alignment == "JUSTIFIED"){
                newPhrase.hAlign = OF_TEXT_ALIGN_JUSTIFIED;
            } else if ( alignment == "CENTER"){
                newPhrase.hAlign = OF_TEXT_ALIGN_CENTER;
            }
            
            alignment = XML.getValue("vAlign", "TOP");
            
            if (alignment == "TOP"){
                newPhrase.vAlign = OF_TEXT_ALIGN_TOP;
            } else if ( alignment == "BOTTOM"){
                newPhrase.vAlign = OF_TEXT_ALIGN_BOTTOM;
            } else if ( alignment == "MIDDLE"){
                newPhrase.vAlign = OF_TEXT_ALIGN_MIDDLE;
            } 
            
            script.push_back(newPhrase);
            
            XML.popTag();
        }
        
        countDown = waitingTime;
        currentLine = -1;
        bWaiting = true;
    }

    return success;
}

void  ofxTextSequencer::showMessage(string _message, ofxHorizontalAlignment _hAlign, ofxVerticalAlignment _vAlign, float _speed){
    bMessage = true;
    
    message.text = _message;
    message.seconds = message.text.length() * secondsForChar;
    message.speed = _speed;
    message.hAlign = _hAlign;
    message.vAlign = _vAlign;
    
    subsChars(message.text);
    
    if (bWaiting){
        countDown = 0;
    } else {
        float halfOfTime = seconds*0.5;
        if (countDown < halfOfTime){
            countDown = halfOfTime + ( halfOfTime - countDown ); 
        }
        
        speed = 2.0;
    }
}

void ofxTextSequencer::setNextPhrase(ofxTextPhrase &_phrase ){
    countDown   = _phrase.seconds;
    seconds     = _phrase.seconds;
    speed       = _phrase.speed;
    
    textBlock.set(x,y,width,height);
    textBlock.setText( _phrase.text );
    textBlock.setAlignment(script[currentLine].hAlign, script[currentLine].vAlign);
}

void ofxTextSequencer::draw(){
    
    if ( bWaiting ){
        
        //  Waiting time between phrase and phrase
        //
        countDown -= 1/ofGetFrameRate();
        
        if ( countDown <= 0){
            
            //  If the waiting ends load the a phrase
            //
            bWaiting = false;
            
            if (!bMessage){
                
                //  If there is not any message on the pull
                //  jump to next phrase of the script
                //
                currentLine = (currentLine+1)%script.size();
                setNextPhrase( script[currentLine] );
                
            } else {
                
                bMessage = false;
                setNextPhrase( message );
            }
        }
    } else {
        textBlock.draw();
        
        if ( countDown <= 0){
            bWaiting = true;
            countDown = waitingTime;
        }
        
        countDown -= (1/ofGetFrameRate())*speed;
    } 
}