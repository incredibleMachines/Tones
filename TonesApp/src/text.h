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

#define PORTTEXT 7002


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

