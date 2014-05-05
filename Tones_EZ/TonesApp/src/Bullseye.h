//
//  Bullseye.h
//  Tones
//
//  Created by Incredible Machines on 8/23/13.
//
//

#pragma once

#include "ofMain.h"
#include "TonesOSC.h"
#include "ofxTextSuite.h"

class Line {
public:
    ofPolyline polyline;
    int zone;
    int lastZone;
    int ring;
    int lastRing;
    bool active;
    bool noteOnSent;
    bool noteOffSent;
};


class Bullseye{
    
public:
    void setup();
    void update();
    void draw();
    void updateTweetCopy();
    void toggleTranslucentMode();
    void loadImages();

    
    bool translucentMode;
    vector <Line> lines; //draws the bullseye
    vector <ofPoint> pts; //holds all current points (blob positions)
    
    TonesOSC osc;
    
    string currentTweet;
    string currentUser;
    
    int radius;
    int innerRadius;
    
    vector< vector<ofImage> > highlights;
    
    
    ofxTextBlock        tweetText;
    ofxTextBlock        userText;
    TextBlockAlignment  tweetAlignment;
    TextBlockAlignment  userAlignment;  
    
    ofImage bgImg;
    
    bool active[6];
    
};