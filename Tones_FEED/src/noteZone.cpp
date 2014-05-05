//
//  noteZone.cpp
//  noteZone
//
//  Created by Francisco Zamorano on 3/2/13.
//
//

#include "noteZone.h"




//===========================================================
//============= ZONE ========================================
//===========================================================

//-------------------------------------------------
void noteZone::setup(ofVec2f _pos, int zId){
    pos = _pos;
    zoneId = zId;
    numNotes = 5;
    bActive=false;
    posOffset = 0;
    
    
    hSpread.set(1,0);
    vSpread.set(0,1);
    hSpreadScale = 100;
    vSpreadScale = 10;
    
    hSpread.scale(hSpreadScale);
    vSpread.scale(vSpreadScale);


    for (int i=0; i<numNotes; i++) {
        unit tempUnit;
        units.push_back(tempUnit);
    }
    
    for (int i=0; i<units.size(); i++) {
        int tempDirection;
        
        if (i%2==0) {
            tempDirection = 1;
        }else{
            tempDirection = -1;
        }
        units[i].setup(pos + (hSpread/numNotes)* i + vSpread * tempDirection, tempDirection, vSpreadScale);
        units[i].unitColor.setHsb(20+10*i, 140, 200);

    }        
}
//-------------------------------------------------
void noteZone::update(int _note){
    
    
    currentPos = pos *2 * posOffset;
    
    for (int i=0; i<units.size(); i++) {
        
    }
    
    for (int i=0; i>units.size(); i++) {
        if(_note==i){
            units[i].pos = currentPos;
            units[i].update(true);
            units[i].scale = 5*i;

        }else{
            units[i].pos = currentPos;
            units[i].update(false);
            units[i].scale = 0.5;
        }
    }
}

//-------------------------------------------------
void noteZone::draw(){
    
    
    ofPushMatrix();
    ofTranslate(currentPos);
    for (int i=0; i<units.size(); i++) {
        units[i].draw();
    }
    ofPopMatrix();
    
    
    
//    ofCircle(currentPos, 10);

    
}

//===========================================================
//============= UNIT ========================================
//===========================================================

void unit::setup(ofVec2f _pos, int d, float s){
    pos = _pos;
    direction = d;
    
    unitColor.setHsb(0, 200, 95);
    
    scale = 1.0f;
    bActiveUnit = false;
    expandSpeed = 0.5;
    contractSpeed = 0.05;
    unitSpreadFromCenter.set(0,s*2);
    unitDiagonal.set(40,0);
    
}

void unit::update(bool _bActive){
    bActiveUnit=_bActive;
}

void unit::draw(){

    ofPushStyle();
    //animate
    if (bActiveUnit) {
        scale = expandSpeed   * 1 + (1-expandSpeed) * scale;
        ofSetColor(240,255,80);
    }else{
        scale = contractSpeed * 0 + (1-contractSpeed) * scale;
        ofSetColor(unitColor);
    }
    
    circle.draw(pos + unitSpreadFromCenter*scale*direction, 10 + 10*scale);
    line.draw(pos, pos-unitSpreadFromCenter*direction);
    
    ofPopStyle();
}

//===========================================================
//============= SHAPES ======================================
//===========================================================

//CIRCLE CLASS
void circle::draw(ofVec2f _pos, float _scale){
    color.setHsb( 200- 10*_scale, 100+3 *_scale, 50 + 10 * _scale);
//    color.setHsb( 0,10,10);
    color.setHsb(255, 150, 10);
    ofSetColor(color);
    ofCircle(_pos, _scale);
}

//LINE CLASS
void line::draw(ofVec2f _pos1, ofVec2f _pos2){
    ofLine(_pos1, _pos2);
}


    










