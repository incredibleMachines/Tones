//
//  visualPlayer.h
//  Tones
//
//  Created by Francisco Zamorano on 2/27/13.
//
//

#ifndef __Tones__visualPlayer__
#define __Tones__visualPlayer__

#include <iostream>
#include "ofMain.h"
#include "zones.h"
#include "noteZone.h"


class visualPlayer {
    
public:
    visualPlayer();
    
    void setup(int _id);
    void update();
    void draw();
    void updatePoints(ofVec2f _origin, ofVec2f _handle);

    int visualPlayerId;
    
    ofVec2f origin;
    ofVec2f handle;
    ofVec2f handleDefault;
    ofVec2f baseLine;
    ofVec2f baseLineDefault;
    ofVec2f playerPos;
    ofVec2f viewerOrigin;
    ofVec2f viewerBaseline;
    
    float baseLength;
    
    float   angle, angleDeg;
    
    bool    bActive;
    int     numNotes;
    int     note;
    float   playerPosPct;
    
//    vector<zone>zones;
    noteZone zone;

    
    float buttonZoneWidth, buttonZoneHeight, viewerOffset;
    
    int viewerWidth;
    
    ofPolyline shape;

};

#endif /* defined(__Tones__visualPlayer__) */
