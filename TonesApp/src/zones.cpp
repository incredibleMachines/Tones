//
//  zones.cpp
//  Animated_button
//
//  Created by Francisco Zamorano on 2/23/13.
//
//

#include "zones.h"


//--------------------------------------------------------------------
zone::zone(){
    scale=1.0f;    
    timer= 0;
    fadeTime = 0.75f;
    fadeStartTime= 0;
    fadePct = 0;
    expandSpeed = 0.9;
    contractSpeed = 0.05;
    
    v1.set(-1,0);
    v2.set(0,1);
    v3.set(1,0);
    v4.set(0,-1);
    
    bActive=false;
}

//--------------------------------------------------------------------
void zone::setup(float px, float py, float width, float height){
    
    buttonHeight = height;
    posOffset = 100;
    
    v1.scale(width);
    v2.scale(height);    
    pos.set(px,py);

    v3 = v2 - v1 * 0.5;
    v4 = v3 + v1;
    
    a = pos;
    b = pos + v1;
    c = pos + v1 * 1.5 + v2;
    d = pos + v1 + v2 * 2;
    e = pos + v2 * 2;
    f = pos + v1 * 0.5 + v2;
    
    g = a - v3;
    h = b - v3;
    
    wingPoints.push_back(a);
    wingPoints.push_back(b);
    wingPoints.push_back(c);
    wingPoints.push_back(d);
    wingPoints.push_back(e);
    wingPoints.push_back(f);
    
    wing.addVertices(wingPoints);
    wing.setClosed(true);

}

//--------------------------------------------------------------------
void zone::update(int note, int i){
    zoneId = i;    
    bActive=false;
    if(note==i){
        bActive=true;
    }

    //animate
    
    if (bActive) {
        scale = expandSpeed   * 0.75 + (1-expandSpeed) * scale;
    }else{
        scale = contractSpeed * 0 + (1-contractSpeed) * scale;
    }
    wing[0] = a - v4*scale;
    wing[1] = b - v4*scale;
    wing[3] = d + v3*scale;
    wing[4] = e + v3*scale;
}

//--------------------------------------------------------------------
void zone::draw(){
    
    ofPushMatrix();
    ofTranslate(posOffset, -buttonHeight);
    ofPushStyle();
    
    if (bActive){
        ofColor color;
        color.setHsb(50+10*zoneId, 40+40*zoneId, 100+95*zoneId);
        ofSetColor(color);
    }else{
        ofColor color;
        color.setHsb(30+10*zoneId, 40+40*zoneId, 100+95*zoneId);
        ofSetColor(color);
    }

    ofFill();
    ofBeginShape();
    for(int i=0; i<wing.getVertices().size();i++){
        ofVertex(wing.getVertices()[i]);
    }
    ofEndShape();
    
//    wing.draw();
    
    ofPopStyle();//end style
    ofPopMatrix();//end matrix

}

//--------------------------------------------------------------------
void zone::counter(){
    float activeTime = ofGetElapsedTimef();
    float fade = 1;
    float limitTime = 2;
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------

wingUnit::wingUnit(){
    
}

void wingUnit::setup(ofVec2f pos, float spread){
    
}

void wingUnit::update(){
    
}

void wingUnit::draw(){
    
}










