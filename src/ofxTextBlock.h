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

typedef struct {
    string  rawWord;
    float   width;
    float   height;
} wordBlock;

typedef struct {
    public:
    vector<int>   wordsID;
    float   width;
    float   height;
} lineBlock;

//Just a helpful set of enumerated constants.
enum ofxHorizontalAlignment {
    OF_TEXT_ALIGN_LEFT, 
    OF_TEXT_ALIGN_RIGHT, 
    OF_TEXT_ALIGN_JUSTIFIED, 
    OF_TEXT_ALIGN_CENTER 
};

enum ofxVerticalAlignment {
    OF_TEXT_ALIGN_TOP, 
    OF_TEXT_ALIGN_BOTTOM, 
    OF_TEXT_ALIGN_MIDDLE 
};

class ofxTextBlock: public ofRectangle {
public:
    ofxTextBlock();

    void    init(string fontLocation, float fontSize);

    void            setText(string _inputText);
    ofxTextBlock&   setScale(float _scale){ scale = _scale; return * this;};
    ofxTextBlock&   setLineHeight(float lineHeight){ font.setLineHeight(lineHeight); return * this;};
    ofxTextBlock&   setAlignment(ofxHorizontalAlignment _hAlignment , ofxVerticalAlignment _vAlignment = OF_TEXT_ALIGN_TOP);
    ofxTextBlock&   setWrapping(bool _bWraping){ bWraping = _bWraping; return * this; };
    
    float   getTextWidth();
    float   getTextHeight();
    
    void    draw();
    
protected:
    void    _loadWords();

    void    _trimLineSpaces();
    float   _getWidthOfWords();
    int     _getLinedWords();
    
    int     _wrapTextX(float lineWidth);                 //Returns the number of lines it formed.
    void    _wrapTextArea(float rWidth, float rHeight);
    bool    _wrapTextForceLines(int linesN);
    
    void    _forceScale(float _scale);
    
    ofTrueTypeFont          font;
    
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
