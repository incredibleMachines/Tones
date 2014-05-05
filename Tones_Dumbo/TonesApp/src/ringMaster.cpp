//
//  ringMaster.cpp
//  lunarlon
//
//  Created by Francisco Zamorano on 8/31/13.
//
//


#include "ringMaster.h"

//--------------------------------------------------------------
void RingMaster::setup(){
    // Main Center Position
    centerOfRings.set(ofGetWidth()/2, ofGetHeight()/2);
    
    
    // Rings init values
    nRings = 25;
    int nParticlesRingZero = 10;
    particleDist = 20;
    particleSpringiness = 0.09;
    float initRadius = 50;
    breathing = 0.08;
    
    for (int i=0; i<nRings; i++) {
        Ring tempRing;
        rings.push_back(tempRing);
    }
    
    for (int i=0; i<rings.size(); i++) {
        rings[i].setup(nParticlesRingZero + 3 * i, centerOfRings, initRadius +  12 * i, particleSpringiness, particleDist);
        rings[i].p2pForceStrength = 0.4;
        rings[i].p2pForceRadius = 9*i;
        ofColor tempColor;
        tempColor.setHsb(80+2*i, 100 + 10*i, 255 - 5*i,255 - 7*i);
        rings[i].setColor(tempColor);
    }
}

//--------------------------------------------------------------
void RingMaster::update(vector<ofPoint>_blobs, TonesOSC& oscIn){
    
    beat = oscIn.beatOn;
    
    if(beat){
        reactionAmt = 0.2;
    } else reactionAmt = 0.0;
    
    blobs.clear();
    blobs = _blobs;
    
    //update blobs positions in rings
    for (int i=0; i<rings.size(); i++) {
        rings[i].updateForces(_blobs);
        rings[i].p2pForceStrength = 0.1 + reactionAmt;
        if (rings[i].p2pForceStrength>0.3) {
            rings[i].p2pForceStrength = 0.3;
        }
        float osc = sin(ofGetElapsedTimef()) * breathing * i;
        rings[i].p2pForceRadius += osc;
    }
}

//--------------------------------------------------------------
void RingMaster::draw(){
            
    //Rings
    for (int i=0; i<rings.size(); i++) {
        rings[i].draw();
    }
    
}



