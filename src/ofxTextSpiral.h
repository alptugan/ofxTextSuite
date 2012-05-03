//
//  ofxTextSpiral.h//
//  Created by Patricio González Vivo on 4/25/12.
//  Copyright (c) 2012 PatricioGonzalezVivo.com. All rights reserved.
//

#ifndef OFXTEXTSPIRAL 
#define OFXTEXTSPIRAL

#include "ofMain.h"
#include "ofxTextArc.h"

class ofxTextSpiral: public ofxTextArc {
public:
    ofxTextSpiral(){
        letters = NULL;
        
        scale   = 1.0;
        proportion = 0.5;
        angle   = 0;
        radius  = 300;
        
        hAlignment  =   OF_TEXT_ALIGN_LEFT;
        vAlignment  =   OF_TEXT_ALIGN_TOP;  
    };
    
    virtual void    setRadialProportion(float _proportion){ proportion = _proportion; };

protected:
    void  _loadWords(){
        letters = new letterArc[rawText.length()];
        
        if ( vAlignment == OF_TEXT_ALIGN_TOP){
            proportion = -1.0 * abs(proportion);
        }
        
        totalAngle = 0;
        for (int i=0; i< rawText.length(); i++) {
            
            float scaleFactor = totalAngle/(PI*2);
    
            letters[i].scale  = scale + scaleFactor*proportion;

            letters[i].radius = radius * letters[i].scale;
            letters[i].width = (font.getCharacterWidth(rawText.at(i)) * font.getLetterSpacing()) * letters[i].scale;
            letters[i].angle = atan(letters[i].width / letters[i].radius);
            
            totalAngle += letters[i].angle;
        }
    }
    
    float proportion;
};

#endif
