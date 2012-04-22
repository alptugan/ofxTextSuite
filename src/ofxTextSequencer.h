//
//  AnimatedText.h
//  animatedText
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
    string  text;
    float   speed;
    float   seconds;
    int     align;
} ofxTextPhrase;

typedef struct{  
    string character;  
    string code;  
} charSubstitution;

class ofxTextSequencer: public ofRectangle {
public:
    ofxTextSequencer();
    
    bool    load(string _xmlFile);
    void    setSpeed(float _speed){speed = _speed;};
    void    setWaitingTime( float _time){ waitingTime = _time;};
    
    void    setColor( ofColor &_color) { textBlock.setColor( _color.r, _color.g, _color.b, _color.a); };
    void    setColor( int _b, int _a = 255) { textBlock.setColor( _b, _b, _b, _a); };
    void    setColor( int _r, int _g, int _b, int _a = 255) { textBlock.setColor( _r, _g, _b, _a); };
    
    void    showMessage(string _message);
    
    float   getNormTransitionValue();
    void    draw();
    
private:
    void    subsChars(string & origString);
    vector<ofxTextPhrase>  script;
    
    ofxTextBlock  textBlock;
    
    float   speed;
    float   waitingTime;
    float   secondsForChar;
    
    float   countDown;
    int     currentLine;
    
    bool    bWaiting;
};

#endif
