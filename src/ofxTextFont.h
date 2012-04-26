//
//  ofxTextFont.h
//  ofxArcText-example
//
//  Created by Patricio González Vivo on 4/24/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#ifndef OFXTEXTFONT 
#define OFXTEXTFONT

#include "ofMain.h"

typedef struct{  
    string character;  
    string code;  
} charSubstitution;

static void subsChars(string & origString){  
    static charSubstitution chars[]={ {"à","\xE0"}, {"á","\xE1"}, {"â","\xE2"}, {"ã","\xE3"}, {"ä","\xE4"}, {"æ","\xE6"}, {"ò","\xF2"},{"ó","\xF3"}, {"ô","\xF4"}, {"õ","\xF5"}, {"ö","\xF6"}, {"ù","\xF9"}, {"ú","\xFA"}, {"û","\xFB"}, {"ü","\xFC"}, {"è","\xE8"}, {"é","\xE9"}, {"ê","\xEA"}, {"ë","\xEB"}, {"ì","\xEC"}, {"í","\xED"}, {"î","\xEE"}, {"ï","\xEF"}, {"ç","\xE7"}, {"Ç","\xC7"} };  
    
    for(int i=0; i<24; i++){  
        while(origString.find(chars[i].character) !=string::npos){  
            origString = origString.substr(0,origString.find(chars[i].character)) + chars[i].code + origString.substr(origString.find(chars[i].character)+2);  
        }  
    };  
}

class ofxTextFont: public ofTrueTypeFont {
public:
    
    ofxTextFont(){
        
    }
    
    float getCharacterWidth(char ch){
        if (ch==' ') ch='i';
        return cps[ch-NUM_CHARACTER_TO_START].setWidth;
    }
};
#endif
