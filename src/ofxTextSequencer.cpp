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
    
    defaultFontFile     =   "helvetica.ttf";
    defaultFontSize     =   30.0;
    defaultFontDpi      =   90;
    defaultShape        =   OF_TEXT_SHAPE_BLOCK;
    
    bPlay       = false;
    bMessage    = false;
    
    text        = NULL;
}

bool ofxTextSequencer::load(string _xmlFile){
    bool    success = false;
    
    ofxXmlSettings XML;
    
    
    if (XML.loadFile(_xmlFile)){
        
        //  Font
        //
        defaultFontFile     = XML.getValue("default:font:file", "helvetica.ttf");
        defaultFontSize     = XML.getValue("default:font:size", 30.0);
        defaultFontDpi      = XML.getValue("default:font:dpi", 90);
        
        defaultSpeed        = XML.getValue("default:speed", 1.0); 
        secForChar          = XML.getValue("default:secForChar", 0.2);
        secBetweenPhrase    = XML.getValue("default:secBetweenPhrase", 2.0);
        
        string defShape     = XML.getValue("default:shape", "BLOCK");
        if (defShape == "BLOCK"){
            defaultShape = OF_TEXT_SHAPE_BLOCK;
        } else if (defShape == "ARC"){
            defaultShape = OF_TEXT_SHAPE_ARC;
        } else if (defShape == "SPIRAL"){
            defaultShape = OF_TEXT_SHAPE_SPIRAL;
        }
        
        string defVerAlign = XML.getValue("default:hAlign", "CENTER");
        if (defVerAlign == "TOP"){
            defaultVertAlign = OF_TEXT_ALIGN_TOP;
        } else if ( defVerAlign == "BOTTOM"){
            defaultVertAlign = OF_TEXT_ALIGN_BOTTOM;
        } else if ( defVerAlign == "MIDDLE"){
            defaultVertAlign = OF_TEXT_ALIGN_MIDDLE;
        }
        
        string defHorAlign = XML.getValue("default:vAlign", "TOP");
        if (defHorAlign == "LEFT"){
            defaultHoriAlign = OF_TEXT_ALIGN_LEFT;
        } else if ( defHorAlign == "RIGHT"){
            defaultHoriAlign = OF_TEXT_ALIGN_RIGHT;
        } else if ( defHorAlign == "JUSTIFIED"){
            defaultHoriAlign = OF_TEXT_ALIGN_JUSTIFIED;
        } else if ( defHorAlign == "CENTER"){
            defaultHoriAlign = OF_TEXT_ALIGN_CENTER;
        }
        
        int totalLines = XML.getNumTags("phrase");
        for(int i = 0; i < totalLines; i++){
            XML.pushTag("phrase",i);
            textPhrase newPhrase;
            
            //  Text Phrase
            //
            newPhrase.text      =   XML.getValue("text", "NO TEXT FOUND");
            newPhrase.seconds   =   newPhrase.text.length() * secForChar;
            
            //  Atributes
            //
            newPhrase.fontFile  =   XML.getValue("font:file", defaultFontFile);
            newPhrase.fontSize  =   XML.getValue("font:size", defaultFontSize);
            newPhrase.fontDpi   =   XML.getValue("font:dpi", defaultFontDpi);
            newPhrase.speed     =   XML.getValue("speed", defaultSpeed);
            newPhrase.scale     =   XML.getValue("scale", 1.0);
            newPhrase.spin      =   XML.getValue("spin", 0);
            
            string shape = XML.getValue("shape", defShape);
            if (shape == "BLOCK"){
                newPhrase.shape = OF_TEXT_SHAPE_BLOCK;
            } else if (shape == "ARC"){
                newPhrase.shape = OF_TEXT_SHAPE_ARC;
            } else if (shape == "SPIRAL"){
                newPhrase.shape = OF_TEXT_SHAPE_SPIRAL;
            }
            
            string alignment = XML.getValue("hAlign", defVerAlign);
            if (alignment == "LEFT"){
                newPhrase.hAlign = OF_TEXT_ALIGN_LEFT;
            } else if ( alignment == "RIGHT"){
                newPhrase.hAlign = OF_TEXT_ALIGN_RIGHT;
            } else if ( alignment == "JUSTIFIED"){
                newPhrase.hAlign = OF_TEXT_ALIGN_JUSTIFIED;
            } else if ( alignment == "CENTER"){
                newPhrase.hAlign = OF_TEXT_ALIGN_CENTER;
            }
            
            alignment = XML.getValue("vAlign", defHorAlign);
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
        
        if (totalLines > 0)
            bMessage = false;
        
        countDown = secBetweenPhrase;
        currentLine = -1;
        bWaiting = true;
    } else {
        ofLog(OF_LOG_ERROR, "File " + ofToDataPath(_xmlFile) + " could not be opened" );
    }

    return success;
}

void  ofxTextSequencer::showMessage(string _message, horizontalAlignment _hAlign, verticalAlignment _vAlign, float _speed){
    bMessage = true;
    
    message.text    =   _message;
    message.seconds =   message.text.length() * secForChar;
    message.speed   =   _speed;
    
    message.hAlign  =   _hAlign;
    message.vAlign  =   _vAlign;
    message.scale   =   1.0;
    message.shape   =   defaultShape;
    message.fontFile=   defaultFontFile;
    message.fontSize=   defaultFontSize;
    message.fontDpi =   defaultFontDpi;
    message.spin    =   0;
}

void ofxTextSequencer::showMessage( textPhrase &_phrase ){
    bMessage = true;
    
    message = _phrase;
    
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

void ofxTextSequencer::setNextPhrase(textPhrase &_phrase ){
    rawText     = _phrase.text;
    spin        = _phrase.spin;
    
    seconds = _phrase.seconds;
    
    if (spin > 0){
        seconds = (rawText.length() + spin*2) * secForChar;
    }
    
    countDown   = seconds;
    speed       = _phrase.speed;

    delete  text;
    text = NULL;
    
    switch (_phrase.shape) {
        case OF_TEXT_SHAPE_BLOCK:
            text = new ofxTextBlock();
            break;
        case OF_TEXT_SHAPE_ARC:
            text = new ofxTextArc();
            break;
        case OF_TEXT_SHAPE_SPIRAL:
            text = new ofxTextSpiral();
            break;
    }
    
    if (text != NULL){
        text->loadFont( _phrase.fontFile, _phrase.fontSize, _phrase.fontDpi );
        text->set(x,y,width,height);
        text->setScale( _phrase.scale );
        text->setText( _phrase.text );
        text->setAlignment(_phrase.hAlign, _phrase.vAlign);
    }
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
        
        if (text != NULL){
            if ( spin > 0){
                text->setText(spinningString( rawText, spin , (1.0-(countDown/seconds))*(rawText.size()+spin) ));
            }
            text->draw();
        } else
            ofLog(OF_LOG_ERROR,"Text trying to be render with out loading it");
        
        if ( countDown <= 0){
            bWaiting = true;
            countDown = secBetweenPhrase;
        }
        
        countDown -= (1/ofGetFrameRate())*speed;
    } 
}

string ofxTextSequencer::spinningString(string _orginalText, int _nChars, int _offset){
    string rta;
    
    int indexText = 0;
    
    if ( _offset > _nChars){
        indexText = _offset - _nChars;
    }
    for (int i = 0; i < (_orginalText.size()+_nChars); i++){
        
        if ( i < _nChars){
            if ( i >= _nChars - _offset){
                if ( indexText < _orginalText.size())
                    rta += _orginalText[indexText];
                else 
                    rta += " ";
                indexText++;
            } else 
                rta += " ";
        }
    }
    
    return rta;
}