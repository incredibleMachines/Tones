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
#include "ringMaster.h"

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
    long activeTimestamp;
};


class Bullseye{
    
public:
    void setup();
    void update();
    void draw();
    void updateTweetCopy();
    void toggleTranslucentMode();
    void loadImages();
    void drawLines(int i, ofVec2f _zonePerp);
    
    bool translucentMode;
    vector <Line> lines; //draws the bullseye
    vector <ofPoint> pts; //holds all current points (blob positions)
    
    TonesOSC osc;
    
    string currentTweet;
    string currentUser;
    
    int instruments;
    int radius;
    int innerRadius;
    
    vector< vector<ofImage> > highlights;
    
    //-- styling
    vector< ofMesh> meshes;
    ofMesh bgMesh;
    ofImage bgImg;
    RingMaster ringMaster;
    ofTexture bgTex;
    ofShader  shader;
    
    
    
    //-- tweets
    ofxTextBlock        tweetText;
    ofxTextBlock        userText;
    TextBlockAlignment  tweetAlignment;
    TextBlockAlignment  userAlignment;  
    
    bool fading[30];
    float fadeLength[6];
    int colorMod;
    
    float factor;
    bool active[6];
    
};