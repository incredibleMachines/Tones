//
//  noteZone.h
//  noteZone
//
//  Created by Francisco Zamorano on 3/2/13.
//
//

#include "ofMain.h"

#ifndef __noteZone__noteZone__
#define __noteZone__noteZone__


//===CIRCLE=========

class circle {
public:
    void draw(ofVec2f _pos, float _scale);
    ofVec2f pos;
    ofColor color;
};

//===CIRCLE=========
class line {
public:
    void draw(ofVec2f _pos1, ofVec2f _pos2);
};

//============= UNIT ========================================

class unit {
    
public:
    
    void setup(ofVec2f _pos, int d, float s);
    void update(bool _bActive);
    void draw();
    float animate();
    
    int unitId;
    ofVec2f pos;
    
    bool bActiveUnit;
    float scale;
    float expandSpeed, contractSpeed;
    int direction;
    ofVec2f unitSpreadFromCenter;
    ofVec2f unitDiagonal;
    ofColor unitColor;
    
    
    circle circle;
    line line;

};

//============= ZONE ========================================
class noteZone {

public:
    
    void setup(ofVec2f _pos, int zId);
    void update(int _note);
    void draw();

    int zoneId; //determines which vis
    bool bActive;
    int note;
    int numNotes;
    int nUnits;
    
    ofVec2f hSpread, vSpread;
    float   hSpreadScale, vSpreadScale;
    ofVec2f pos;
    float posOffset;
    ofVec2f currentPos;

    
    vector<unit> units;
      
};






#include <iostream>

#endif /* defined(__noteZone__noteZone__) */
