//
//  text.h
//  textDrawer
//
//  Created by incredible_machines on 2/27/13.
//
//


#pragma once

#include "ofxOsc.h"
#include "ofxTextSuite.h"

#define PORT 7000


class Text{

    
    public:
    void setup();
    void update();
    void draw();
    
    ofxOscReceiver incomingText;
    string tweetString;
    string userString;
    
    ofxTextBlock tweetText;
    ofxTextBlock userText;


};

