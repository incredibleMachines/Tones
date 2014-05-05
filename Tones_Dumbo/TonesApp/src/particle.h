//
//  particle.h
//  Lunarlon_v3
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#ifndef __Lunarlon_v3__particle__
#define __Lunarlon_v3__particle__

#include <iostream>
#include "ofMain.h"

class particle
{
public:
    
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    
    particle();
    virtual ~particle(){};
    
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    void addClockwiseForce(particle &p, float radius, float scale);
    void addCounterClockwiseForce(particle &p, float radius, float scale);
    
    void addDampingForce();
    void bounceOffWalls();
    
    void setInitialCondition(float px, float py, float vx, float vy, float _damping);
    void update();
    void draw();

    void changeColor(ofVec2f _pos, float _radius);
    
    
    ofColor color;
    bool bFixed;
    float damping;
    float particleRadius;
    
    
protected:
private:
    
    
    
    
};

#endif /* defined(__Lunarlon_v3__particle__) */
