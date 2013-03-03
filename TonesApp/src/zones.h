//
//  zones.h
//  Animated_button
//
//  Created by Francisco Zamorano on 2/23/13.
//
//

#ifndef __Animated_button__zones__
#define __Animated_button__zones__

#include <iostream>
#include "ofMain.h"

class wingUnit {
public:
    wingUnit();
    void setup(ofVec2f pos, float spread);
    void update();
    void draw();
};


class zone {
public:
    
    zone();
    void setup(float px, float py, float width, float height);
    void update(int ring, int i);
    void draw();
    void counter();
    

    
    
    float   timer;
    float   fadeTime;
    float   fadeStartTime;
    float   fadePct;

    ofVec2f pos;
    float   posOffset;
    float   scale;
    ofVec2f size;
        
    bool    bActive;
    float   expandSpeed;
    float   contractSpeed;

    ofPolyline shape;
    vector<ofPoint>shapePoints;
    vector<ofPoint>wingPoints;
    ofVec2f a, b, c, d, e, f, g, h;    
    ofVec2f v1, v2, v3, v4;
    
    int ringId;
    int zoneId;
        
    ofPolyline wing;
    
    ofColor color;
    
    float buttonHeight;
    
    wingUnit wUnit;
};










#endif /* defined(__Animated_button__zones__) */
