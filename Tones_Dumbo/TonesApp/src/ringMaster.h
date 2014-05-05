//
//  ringMaster.h
//  lunarlon
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#ifndef __lunarlon__ringMaster__
#define __lunarlon__ringMaster__

#include <iostream>
#include "ofMain.h"
#include "ring.h"
#include "ofxSyphon.h"
#include "TonesOSC.h"


class RingMaster {
    
    
public:
    void setup();
    void update(vector<ofPoint>_blobs, TonesOSC& oscIn);
    void draw();

    
    // Rings
    vector<Ring>rings;
    ofVec2f centerOfRings;
    int nRings;

    // Particles
    float particleDist;
    float particleSpringiness;
    
    // Blob positions
    vector<ofPoint>blobs;
    
    // Animation
    float breathing;
    float reactionAmt;
    
    
    bool beat;
};

#endif /* defined(__lunarlon__ringMaster__) */
