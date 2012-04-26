//
//  ofxTextArc.h
//
//  Created by Patricio González Vivo on 4/23/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//
//  Based on: https://github.com/companje/ofxArcText by campanje

#ifndef OFXTEXTARC_H
#define OFXTEXTARC_H

#include "ofMain.h"

#include "ofxTextFont.h"
#include "ofxTextAlignment.h"

typedef struct {
    float       angle;
    float       width;
    float       radius;
    float       scale;
} letterArc;

class ofxTextArc {
public:
    ofxTextArc();
    
    virtual void    loadFont(string _fontLocation, float _fontSize, int _dpi = 90);
    
    virtual void    setText(string _inputText);
    virtual void    setScale(float _scale){ scale = _scale; };
    virtual void    setRadius(float _radius){ radius = _radius; _loadWords(); };
    virtual void    setAngle(float _angle){ angle = _angle; _loadWords(); };
    virtual void    setAlignment(ofxHorizontalAlignment _hAlignment , ofxVerticalAlignment _vAlignment = OF_TEXT_ALIGN_TOP);
    
    virtual int     length(){return rawText.length();};
    virtual void    clear(){ rawText.clear();};
    virtual ofxTextArc& operator += (string _text){ setText(rawText + _text);}; 
    virtual ofxTextArc& operator = (string _text){ setText(_text);}; 
    virtual ofxTextArc& operator -- (){ if( rawText.length()>0){ rawText.erase( rawText.begin() ); setText(rawText); }};
    virtual ofxTextArc& operator -- (int){ if( rawText.length()>0){ rawText.erase(rawText.end()-1); setText(rawText); }};
    
    virtual void    draw(float _x, float _y);
    
protected:
    virtual void  _loadWords();
    
    ofxTextFont             font;
    
    ofxHorizontalAlignment  hAlignment;
    ofxVerticalAlignment    vAlignment;
    
    letterArc               *letters;
    string                  rawText;
    float                   angle, totalAngle, radius;
    float                   scale;
};

#endif
