//
//  ofxTextSequencer.h
//
//  Created by Patricio González Vivo on 4/9/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#ifndef ANIMATEDTEXT
#define ANIMATEDTEXT

#include "ofMain.h"

#include "ofxTextShape.h"

#include "ofxTextArc.h"
#include "ofxTextBlock.h"
#include "ofxTextSpiral.h"

#include "ofxXmlSettings.h"

typedef struct {
    string                  text, fontFile;
    float                   seconds, speed, scale, fontSize, fontDpi;
    int                     spin;
    textShape               shape;
    horizontalAlignment     hAlign;
    verticalAlignment       vAlign;
} textPhrase;

class ofxTextSequencer: public ofRectangle {
public:
    ofxTextSequencer();
    
    void    setSpeed(float _speed){ speed = _speed;};
    void    setSecForChar( float _secForChar){ secForChar = _secForChar; };
    void    setSecBetweenPhrases( float _secBetweenPhrase){ secBetweenPhrase = _secBetweenPhrase;};
    void    setNextPhrase(textPhrase &_phrase );
    
    float   getNormTransitionValue(){ return sin( (countDown/seconds) * PI );};
    
    bool    load(string _xmlFile);
    void    play(){ bPlay = true; };
    
    void    stop(){ bPlay = false;};
    void    showMessage( textPhrase &_phrase );
    void    showMessage(string _message, horizontalAlignment _hAlign = OF_TEXT_ALIGN_LEFT, verticalAlignment _vAlign = OF_TEXT_ALIGN_TOP, float _speed = 1.0 );
    
    void    draw();
    
private:
    string      spinningString(string _orginalText, int _nChars, int _offset);
    vector<textPhrase> script;
    textPhrase      message;
    
    string          rawText;
    ofxTextShape    *text;
    
    textShape   defaultShape;
    string      defaultFontFile;
    float       defaultFontSize, defaultFontDpi, defaultSpeed;
    verticalAlignment   defaultVertAlign;
    horizontalAlignment defaultHoriAlign;
    
    float   secBetweenPhrase, secForChar;
    float   speed, seconds, countDown;
    int     currentLine, spin;
    
    bool    bWaiting, bMessage, bPlay;
};

#endif
