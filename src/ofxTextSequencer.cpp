//
//  AnimatedText.cpp
//  animatedText
//
//  Created by Patricio González Vivo on 4/9/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#include "ofxTextSequencer.h"

ofxTextSequencer::ofxTextSequencer(){
    currentLine = 0;
}

bool ofxTextSequencer::load(string _xmlFile){
    bool    success = false;
    
    ofxXmlSettings XML;
    
    if (XML.loadFile(_xmlFile)){
        string fontFile = XML.getValue("font", "helvetica.ttf");
        float fontSize = XML.getValue("fontSize", 30.0);
        secondsForChar = XML.getValue("secondForChar", 0.2);
        waitingTime = XML.getValue("waitingTime", 2.0);
        
        textBlock.init( fontFile, 
                       fontSize);
        cout << "Font: " << fontFile << endl;
        cout << "Size: " << fontSize << endl;
        
        textBlock.setColor(0, 0, 0, 255);
        
        int totalLines = XML.getNumTags("phrase");
        
        for(int i = 0; i < totalLines; i++){
            XML.pushTag("phrase",i);
            ofxTextPhrase newPhrase;
            
            newPhrase.text = XML.getValue("text", "Text");
            newPhrase.seconds = newPhrase.text.length() * secondsForChar;
            newPhrase.speed = XML.getValue("speed", 1.0);
            
            subsChars(newPhrase.text);
            string alignment = XML.getValue("align", "LEFT");
            
            if (alignment == "LEFT"){
                newPhrase.align = 0;
            } else if ( alignment == "RIGHT"){
                newPhrase.align = 1;
            } else if ( alignment == "JUSTIFIED"){
                newPhrase.align = 2;
            } else if ( alignment == "CENTER"){
                newPhrase.align = 3;
            }
            
            script.push_back(newPhrase);
            
            XML.popTag();
        }
        
        cout << script.size() << " lines loaded" << endl;
        
        countDown = waitingTime;
        currentLine = -1;
        bWaiting = true;
    }

    return success;
}

void  ofxTextSequencer::showMessage(string _message){
    
}

float ofxTextSequencer::getNormTransitionValue(){
    float rta = 0;
    if ((currentLine > -1) &&
        (currentLine < script.size()) ){
            
        rta = sin( (countDown/script[currentLine].seconds ) * PI );
    }
        
    return rta;
}

void ofxTextSequencer::subsChars(string & origString){  
    static charSubstitution chars[]={ {"à","\xE0"}, {"á","\xE1"}, {"â","\xE2"}, {"ã","\xE3"}, {"ä","\xE4"}, {"æ","\xE6"}, {"ò","\xF2"},{"ó","\xF3"}, {"ô","\xF4"}, {"õ","\xF5"}, {"ö","\xF6"}, {"ù","\xF9"}, {"ú","\xFA"}, {"û","\xFB"}, {"ü","\xFC"}, {"è","\xE8"}, {"é","\xE9"}, {"ê","\xEA"}, {"ë","\xEB"}, {"ì","\xEC"}, {"í","\xED"}, {"î","\xEE"}, {"ï","\xEF"}, {"ç","\xE7"}, {"Ç","\xC7"} };  
    
    for(int i=0; i<24; i++){  
        while(origString.find(chars[i].character) !=string::npos){  
            origString = origString.substr(0,origString.find(chars[i].character)) + chars[i].code + origString.substr(origString.find(chars[i].character)+2);  
        }  
    };  
}

void ofxTextSequencer::draw(){
    
    if ( bWaiting ){
        
        //  Waiting time between phrase and phrase
        //
        countDown -= 1/ofGetFrameRate();
        
        if ( countDown <= 0){
            
            //  If the waiting ends go to the next phrase.
            //
            bWaiting = false;
            currentLine = (currentLine+1)%script.size();
            textBlock.setText( script[currentLine].text );
            //textBlock.wrapTextArea(width, height);
            textBlock.wrapTextX(width);
            countDown = script[currentLine].seconds;
            cout << "Loading next Phrase: " << script[currentLine].text << endl;
        }
    } else {
        ofSetColor(255, 255, 255);
        
        if (script[currentLine].align == 0){
            textBlock.drawLeft(x, y);
        } else if (script[currentLine].align == 1){
            textBlock.drawRight(x + width - textBlock.getWidth(), y);
        } else if (script[currentLine].align == 2){
            textBlock.drawJustified(x, y, width);
        } else if (script[currentLine].align == 3){
            textBlock.drawCenter(getCenter().x, getCenter().y);
        }
        
        if ( countDown <= 0){
            bWaiting = true;
            countDown = waitingTime;
        }
        
        countDown -= (1/ofGetFrameRate())*script[currentLine].speed;
    } 
}