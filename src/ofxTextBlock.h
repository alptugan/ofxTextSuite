/***********************************************************************

 Copyright (c) 2009, Luke Malcolm, www.lukemalcolm.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***********************************************************************/

#ifndef OFXTEXTBLOCK_H
#define OFXTEXTBLOCK_H

#include "ofMain.h"
#include <iterator>

#include "ofxTextFont.h"
#include "ofxTextAlignment.h"

typedef struct {
    string      rawWord;
    float       width;
    float       height;
} wordBlock;

typedef struct {
    vector<int> wordsID;
    float       width;
    float       height;
} lineBlock;

class ofxTextBlock: public ofRectangle {
public:
    ofxTextBlock();

    virtual void    loadFont(string _fontLocation, float _fontSize, int _dpi = 90);

    virtual void    setText(string _inputText);
    virtual void    setScale(float _scale){ scale = _scale; };
    virtual void    setLineHeight(float lineHeight){ font.setLineHeight(lineHeight);};
    virtual void    setAlignment(ofxHorizontalAlignment _hAlignment , ofxVerticalAlignment _vAlignment = OF_TEXT_ALIGN_TOP);
    void    setWrapping(bool _bWraping){ bWraping = _bWraping;};
    
    
    float   getTextWidth();
    float   getTextHeight();
    
    int     length(){return rawText.length();};
    void    clear(){ rawText.clear();};
    ofxTextBlock& operator += (string _text){ setText(rawText + _text);}; 
    ofxTextBlock& operator = (string _text){ setText(_text);}; 
    ofxTextBlock& operator -- (int){ if( rawText.length()>0){ rawText.erase(rawText.end()-1); setText(rawText); } };
    
    void    draw();
    void    draw(float _x, float _y, float _w = -1, float _h = -1);
    
protected:
    void    _loadWords();

    void    _trimLineSpaces();
    float   _getWidthOfWords();
    int     _getLinedWords();
    
    int     _wrapTextX(float lineWidth);                 //Returns the number of lines it formed.
    void    _wrapTextArea(float rWidth, float rHeight);
    bool    _wrapTextForceLines(int linesN);
    
    void    _forceScale(float _scale);
    
    ofxTextFont             font;
    
    vector<wordBlock>       words;
    vector<lineBlock>       lines;
    wordBlock               blankSpaceWord;
    
    ofxHorizontalAlignment  hAlignment;
    ofxVerticalAlignment    vAlignment;
    string                  rawText;
    float                   scale;
    bool                    bWraping;
};

#endif // OFXTEXTBLOCK_H
