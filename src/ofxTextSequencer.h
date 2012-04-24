//
//  ofxTextSequencer.h
//
//  Created by Patricio González Vivo on 4/9/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#ifndef ANIMATEDTEXT
#define ANIMATEDTEXT

#include "ofMain.h"
#include "ofxTextBlock.h"
#include "ofxXmlSettings.h"

typedef struct {
    string              text;
    float               speed, seconds;
    ofxHorizontalAlignment hAlign;
    ofxVerticalAlignment   vAlign;
} ofxTextPhrase;

typedef struct{  
    string character;  
    string code;  
} charSubstitution;

class ofxTextSequencer: public ofRectangle {
public:
    ofxTextSequencer();
    
    void    setSpeed(float _speed){speed = _speed;};
    void    setWaitingTime( float _time){ waitingTime = _time;};
    void    setNextPhrase(ofxTextPhrase &_phrase );
    
    float   getNormTransitionValue(){ return sin( (countDown/seconds) * PI );};
    bool    load(string _xmlFile);
    void    play(){ bPlay = true; };
    
    void    stop(){ bPlay = false;};
    void    showMessage(string _message, ofxHorizontalAlignment _hAlign = OF_TEXT_ALIGN_LEFT, ofxVerticalAlignment _vAlign = OF_TEXT_ALIGN_TOP, float _speed = 1.0 );
    
    void    draw();
    
private:
    void    _subsChars(string & origString);
    
    vector<ofxTextPhrase> script;
    ofxTextPhrase   message;
    
    ofxTextBlock  textBlock;
    
    float   waitingTime, secondsForChar;
    float   speed, seconds, countDown;
    int     currentLine;
    
    bool    bWaiting, bMessage, bPlay;
};

#endif
