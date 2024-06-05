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

#define TWEENZOR_ENABLED
#ifdef TWEENZOR_ENABLED
#include "ofxTweenzor.h"
#endif

#include "ofMain.h"
#include <iterator>

class wordBlock {
    public:
        string          rawWord;
        float           width;
        float           height;
        ofColor         color;
    int r,g,b,a;
        ofTrueTypeFont  defaultFont;
        bool            hasFormat;
        bool            isBreakLine;

        void setFont(string fontLocation, float fontSize, bool antiAliased) {
            hasFormat = true;

            defaultFont.load(fontLocation, fontSize, antiAliased, true);

            width = defaultFont.stringWidth(rawWord);
            height = defaultFont.stringHeight(rawWord);
        }
};


class lineBlock {
    public:
        vector<int>   wordsID;

        float   width;
        float   height;

};

class textFormat {
public:
    string    tagOpened="";
    string    tagClosed="";
    string    font = "";
    int        size=0;
    ofColor    color;
    bool antiAliesed=true;
};

//Just a helpful set of enumerated constants.
enum TextBlockAlignment { OF_TEXT_ALIGN_LEFT, OF_TEXT_ALIGN_RIGHT, OF_TEXT_ALIGN_JUSTIFIED, OF_TEXT_ALIGN_CENTER };

class ofxTextBlock
{
    public:
        
        ofxTextBlock();
        virtual ~ofxTextBlock();
        void updateTweenzor();
//#ifdef TWEENZOR_ENABLED
        void enableAnimatedText(bool _val = true);
        void animateText(float time = 1.0, float _delay = 0.0, float _delayRate = 0.2, string _type = "fadein");
        vector<TweenParams> params;
//#endif
        vector<float> currentAlpha;
        string          rawText;
        ofTrueTypeFont  defaultFont;
        wordBlock       blankSpaceWord;
        float           scale;
        int                defaultLineWidth;
        vector<wordBlock>   words;
        vector<lineBlock>   lines;
        vector<textFormat>  formats;


        void    init(string fontLocation, float fontSize, bool antiAliased = true);
        void    init( ofTrueTypeFont *_f, bool antiAliased = true);

        void    setText(string _inputText);
        void    setHtmlText(string _inputText);
        void    setFormat(textFormat format);


        int     wrapTextX(float lineWidth, bool skipBreakLine = false);                 //Returns the number of lines it formed.
        void    wrapTextArea(float rWidth, float rHeight);
        bool    wrapTextForceLines(int linesN);

        void    setLineHeight(float lineHeight);
        void    setColor(int r, int g, int b, int a);
        void    setColor(ofColor _color);

        void    draw(float x, float y);                    //Draws left align.
        void    drawLeft(float x, float y);
        void    drawRight(float x, float y);
        void    drawCenter(float x, float y);
        void    drawJustified(float x, float y, float boxWidth);


        void    forceScale(float _scale);

        float   getWidth();
        float   getHeight();
        glm::vec2 getPos();
        string getAnimType();
        ofTrueTypeFont & getFont();
        ofColor _mainColor;
        ofRectangle getBoundingBox();
    protected:
        void    _loadWords();
        void    _trimLineSpaces();
        float   _getWidthOfWords();
        int     _getLinedWords();
//#ifdef TWEENZOR_ENABLED
        void    _onComplete(float* arg);
        
//#endif
    
    private:
        bool isAnimatedTextEnabled;
        float alphaBegin;
        float alphaEnd;
        int alignmentShiftX;
        string animType;
        glm::vec2 pos;
        vector<ofColor> cls;
};

#endif // OFXTEXTBLOCK_H
