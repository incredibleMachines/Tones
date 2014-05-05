//
//  spring.h
//  Lunarlon_v2
//
//  Created by Francisco Zamorano on 8/24/13.
//
//

#ifndef __Lunarlon_v2__spring__
#define __Lunarlon_v2__spring__

#include <iostream>
#include "ofMain.h"
#include "particle.h"

class Spring {
    
public:
    
    Spring();
    
    particle * particleA;
    particle * particleB;
    
    float distance;
    float springiness;
    
    void update();
    void draw();
    void changeColor(ofPoint _blobPos,float _radius);
    
    ofVec2f frcToAdd;
    ofColor color;
    
    float lineThickness;
    

};


#endif /* defined(__Lunarlon_v2__spring__) */
