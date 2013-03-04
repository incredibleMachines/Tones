//
//  centerVisual.h
//  Tones
//
//  Created by Francisco Zamorano on 2/28/13.
//
//

#ifndef __Tones__centerVisual__
#define __Tones__centerVisual__

#include <iostream>
#include "ofMain.h"
#include "particleRing.h"
#include "ofxOsc.h"
#define PORT_RECEIVE 9000

class centerVisual {
    
public:
    centerVisual();
    void setup(vector<ofPoint>shape, ofPoint ctr);
    void update();
    void draw();
    
    ofPolyline mainShape;
    ofPoint center;
    
    //ParticleRing
    vector <particle *> myParticles;
    vector<ofVec2f>repulsionPoints;
    
    //Receive beats from Live
    ofxOscReceiver beatReceiver;
    string beat1;
    bool bHaveBeat;
    
};


class perimeter {
    
public:

    
};





#endif /* defined(__Tones__centerVisual__) */
