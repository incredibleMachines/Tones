//
//  spring.cpp
//  Lunarlon_v2
//
//  Created by Francisco Zamorano on 8/24/13.
//
//

#include "spring.h"

//------------------------------------------
Spring::Spring(){
    particleA = NULL;
    particleB = NULL;
    lineThickness = 1.5f;
}

//------------------------------------------
void Spring::update(){
    
    if (particleA == NULL || particleB ==NULL) {
        return;
    }
    
    ofVec2f pta = particleA->pos;
    ofVec2f ptb = particleB->pos;
    
    float particleDist = (pta-ptb).length();
    float springForce = (springiness * (distance - particleDist));
    frcToAdd = (pta-ptb).normalized()*springForce;
    
    particleA->addForce(frcToAdd.x, frcToAdd.y);
    particleB->addForce(-frcToAdd.x, -frcToAdd.y);
}

//------------------------------------------
void Spring::draw(){
    
    if (particleA == NULL || particleB ==NULL) {
        return;
    }
    
    ofPushStyle;
    ofSetLineWidth(1);
    ofSetColor(color);
    ofLine(particleA->pos,particleB->pos);
    ofPopStyle;
}

//------------------------------------------
void Spring::changeColor(ofPoint _blobPos,float _radius){
    
    ofVec2f posOfForce;
    posOfForce.set(_blobPos);
    
    ofVec2f diff	= particleA->pos - posOfForce;
	float length	= diff.length();
    
    bool bAmCloseEnough = true;
    if (_radius > 0){
        if (length > _radius){
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
		float pct = 1 - (length / _radius);  // stronger on the inside
//        color.setHsb(170 - 100*pct, 100 + 155*pct, 100 + 155*pct, 220);
        color.setHsb(255, 255,255, 220);
    }
    
    
    
}


