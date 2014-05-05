//
//  ring.h
//  Lunarlon_v3
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#ifndef __Lunarlon_v3__ring__
#define __Lunarlon_v3__ring__

#include <iostream>
#include "particle.h"
#include "spring.h"
#include "ofMain.h"



class Ring{
public:
    
    void setup(int _nParticles, ofPoint _ctr, float _radius, float _springiness, float _distance);
    void setColor(ofColor _color);
    void updateForces(vector<ofPoint>_blobs);
    void updateParticles();
    void draw();
    
    //main position and size
    ofPoint ctr;
    float radius;
    
    //Base color
    ofColor baseColor;
    
    //Blobs
    vector<ofPoint> blobs;
    
    //Particles
    vector<particle>particles;
    vector<particle>originalParticlePos;
    float p2pForceRadius;
    float p2pForceStrength;
    float nParticles;
    
    
    //Springs
    vector<Spring>springs;
    ofMesh mesh;
    
    //Touch controls
    float touchAmt;
    

    
    
    
    
};

#endif /* defined(__Lunarlon_v3__ring__) */
