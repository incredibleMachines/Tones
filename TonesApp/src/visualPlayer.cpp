//
//  visualPlayer.cpp
//  Tones
//
//  Created by Francisco Zamorano on 2/27/13.
//
//

#include "ofMain.h"
#include "visualPlayer.h"

//--------------------------------------------------------------------
visualPlayer::visualPlayer(){
    note = 0;
    
}

//--------------------------------------------------------------------
void visualPlayer::setup(int _id){
    numNotes = 5;
    viewerWidth=100;
    note=0;
    viewerOffset=.7;
    
    playerPos=handle;
    zone.setup(ofVec2f(30,0),_id);

}

//--------------------------------------------------------------------
void visualPlayer::update(){
    if(bActive==true){
        note=(abs(ofDist(playerPos.x,playerPos.y,viewerOrigin.x,viewerOrigin.y))/abs(ofDist(handle.x,handle.y,viewerOrigin.x,viewerOrigin.y)))*numNotes;
        note=(numNotes-1)-note;        
    }
    else{
        note=10;
        playerPos=handle;
    }
    ofVec2f diff = handle - origin;
    float   dist = diff.length();
    angle = atan2(diff.x, diff.y);
    angleDeg = (ofRadToDeg(angle) * -1 - 90) ;
    
    baseLine = handle - origin;
    baseLength = baseLine.length();
    ofVec2f viewerLine=baseLine;
    viewerLine.scale(viewerOffset*baseLine.length());
    viewerOrigin=handle-viewerLine;
    viewerBaseline=viewerLine;
    
    //offset for noteZones and repulsion points
    playerPosPct = ofDist(playerPos.x,playerPos.y, viewerOrigin.x, viewerOrigin.y);
    zone.posOffset = ofMap(playerPosPct, 0, ofDist(handle.x,handle.y,viewerOrigin.x,viewerOrigin.y), 1, 0, true);

    zone.update(note);
    
    for (int i=0; i<numNotes; i++) {
        if (note==i) {
            zone.units[i].bActiveUnit=true;
        }else{
            zone.units[i].bActiveUnit=false;
        }
        if (!bActive) {
            zone.units[i].bActiveUnit=false;
        }
    }
    
}

//--------------------------------------------------------------------
void visualPlayer::updatePoints(ofVec2f _origin, ofVec2f _handle){
    origin = _origin;
    handle = _handle;
    update();
}

//--------------------------------------------------------------------
void visualPlayer::draw(){
    
    ofPushStyle();
    ofFill();
    ofSetColor(255);
    ofCircle(origin, 3); //circle at origin
    ofCircle(handle, 3);
    ofPopStyle();
    
//    ofLine(origin, origin+baseLine); //line between

    
    ofVec2f moveToOrigin = playerPos - origin;

    ///rotate over the main angle
    ofPushMatrix();
    ofTranslate(origin);
    ofRotateZ(angleDeg);
    
    ///DRAW HERE
    
    //player area
    ofNoFill();
    ofSetColor(100, 190, 170);
    ofRect(-baseLength*1.25, -viewerWidth/2, viewerBaseline.length()*1.5, viewerWidth);

    
    //note area
    ofFill();
    zone.draw();

    
//    //draw spotlight
//    ofRect(-baseLine.length()+viewerBaseline.length(), -viewerWidth/2, -viewerBaseline.length(), viewerWidth);

    

    
    ofPopMatrix();
    ///pop
    
    ofLine(origin, origin-baseLine*0.5); //line beyond origin
    
    ///Draw circle for playerPos 
    ofPushStyle();
    ofSetColor(0,255,255,100);
    ofCircle(playerPos,10);
    ofPopStyle();
    
}