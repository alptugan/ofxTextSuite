//
//  ofxTextShape.h
//  ofxArcText-example
//
//  Created by Patricio GonzÃ¡lez Vivo on 4/26/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#ifndef OFXTEXTSHAPE 
#define OFXTEXTSHAPE

#include "ofMain.h"

enum textShape{
    OF_TEXT_SHAPE_BLOCK,
    OF_TEXT_SHAPE_ARC,
    OF_TEXT_SHAPE_SPIRAL
};

enum horizontalAlignment {
    OF_TEXT_ALIGN_LEFT, 
    OF_TEXT_ALIGN_RIGHT, 
    OF_TEXT_ALIGN_JUSTIFIED, 
    OF_TEXT_ALIGN_CENTER 
};

enum verticalAlignment {
    OF_TEXT_ALIGN_TOP, 
    OF_TEXT_ALIGN_BOTTOM, 
    OF_TEXT_ALIGN_MIDDLE 
};

typedef struct{  
    string character;  
    string code;  
} charSubstitution;

class textFont: public ofTrueTypeFont {
public:
    textFont(){
    }
    
    float getCharacterWidth(char ch){
        if (ch==' ') ch='i';
        if (ch=='\xE0') ch='a'; //ˆ
        if (ch=='\xE1') ch='a'; //‡
        if (ch=='\xE2') ch='a'; //‰
        if (ch=='\xE3') ch='a'; //‹
        if (ch=='\xE4') ch='a'; //Š
        if (ch=='\xE6') ch='a'; //¾
        if (ch=='\xE8') ch='e'; //
        if (ch=='\xE9') ch='e'; //Ž
        if (ch=='\xEA') ch='e'; //
        if (ch=='\xEB') ch='e'; //‘
        if (ch=='\xEC') ch='i'; //“
        if (ch=='\xED') ch='i'; //’
        if (ch=='\xEE') ch='i'; //”
        if (ch=='\xEF') ch='i'; //•
        if (ch=='\xF2') ch='o'; //˜
        if (ch=='\xF3') ch='o'; //—
        if (ch=='\xF4') ch='o'; //™
        if (ch=='\xF5') ch='o'; //›
        if (ch=='\xF6') ch='o'; //š
        if (ch=='\xF9') ch='u'; //
        if (ch=='\xFA') ch='u'; //œ
        if (ch=='\xFB') ch='u'; //ž
        if (ch=='\xFC') ch='u'; //Ÿ
        if (ch=='\xC7') ch='c'; //
        return cps[ch-NUM_CHARACTER_TO_START].setWidth;
    }
};

class ofxTextShape : public ofRectangle {
public:
    
    ofxTextShape(){
        rawText     =   "";
        scale       =   1.0f;
        hAlignment  =   OF_TEXT_ALIGN_LEFT;
        vAlignment  =   OF_TEXT_ALIGN_TOP;  };
    
    virtual void    loadFont(string _fontLocation, float _fontSize, int _dpi = 90){
        font.loadFont(_fontLocation, _fontSize, true, true);
        font.setGlobalDpi(_dpi);
    };
    
    virtual void    setText(string _inputText){ 
        _subsChars(rawText);
        _loadWords();
    };
    
    virtual void    setScale(float _scale){ scale = _scale; };
    virtual void    setAlignment(horizontalAlignment _hAlignment , verticalAlignment _vAlignment = OF_TEXT_ALIGN_TOP){
        hAlignment = _hAlignment;
        vAlignment = _vAlignment;
    };
    
    virtual int     length(){return rawText.length();};
    virtual void    clear(){ rawText.clear();};
    
    virtual ofxTextShape& operator += (string _text){ setText(rawText + _text);}; 
    virtual ofxTextShape& operator = (string _text){ setText(_text);}; 
    virtual ofxTextShape& operator -- (){ if( rawText.length()>0){ rawText.erase( rawText.begin() ); setText(rawText); }};
    virtual ofxTextShape& operator -- (int){ if( rawText.length()>0){ rawText.erase(rawText.end()-1); setText(rawText); }};
    
    virtual void    draw(){};
    
protected:
    virtual void    _loadWords(){};
    virtual void    _subsChars(string & origString){  
        
        static charSubstitution chars[]={ {"Ã ","\xE0"}, {"Ã¡","\xE1"}, {"Ã¢","\xE2"}, {"Ã£","\xE3"}, {"Ã¤","\xE4"}, {"Ã¦","\xE6"}, {"Ã²","\xF2"},{"Ã³","\xF3"}, {"Ã´","\xF4"}, {"Ãµ","\xF5"}, {"Ã¶","\xF6"}, {"Ã¹","\xF9"}, {"Ãº","\xFA"}, {"Ã»","\xFB"}, {"Ã¼","\xFC"}, {"Ã¨","\xE8"}, {"Ã©","\xE9"}, {"Ãª","\xEA"}, {"Ã«","\xEB"}, {"Ã¬","\xEC"}, {"Ã­","\xED"}, {"Ã®","\xEE"}, {"Ã¯","\xEF"}, {"Ã§","\xE7"}, {"Ã‡","\xC7"} }; 
        
        for(int i=0; i<24; i++){  
            while(origString.find(chars[i].character) !=string::npos){  
                origString = origString.substr(0,origString.find(chars[i].character)) + chars[i].code + origString.substr(origString.find(chars[i].character)+2);
            }  
        }; 
    }
    
    textFont            font;
    
    horizontalAlignment hAlignment;
    verticalAlignment   vAlignment;
    
    string              rawText;
    float               scale;
};

#endif
