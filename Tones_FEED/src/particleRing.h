//
//  particleRing.h
//  Tones
//
//  Created by Francisco Zamorano on 2/25/13.
//
//

#ifndef __Tones__particleRing__
#define __Tones__particleRing__

#include <iostream>
#include "ofMain.h"

class particle
{
public:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
    
    unsigned int bitFlagW;
    unsigned int bitFlagH;
	
    particle();
    virtual ~particle(){};
    
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    
    void addDampingForce();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();
	
    void bounceOffWalls(ofPolyline outerRing);
    
    ofPoint posinsideHex(ofPolyline outerRing, ofPolyline innerRing);
    
    
    
	
	ofPolyline inRing, outRing;
    ofPoint centroid;
    
    float damping;
    bool bInsideMyRing;
    bool bRedraw;
    
    int ring;
    
    ofColor color;
    ofVec2f moveToCenter;
    ofVec2f innerPos;

    
protected:
private:
};

#endif /* defined(__Tones__particleRing__) */
