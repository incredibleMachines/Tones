//
//  Hexagon.cpp
//  Hexagon
//
//  Created by IncredibleMachines on 2/8/13.
//
//

#include "Hexagon.h"

//--------------------------------------------------------------
void Hexagon::setup(){
    admin.setup();
    cam.setup();
    tex.allocate(1200,960,GL_RGBA);
    
    ///OSC sender
    sender.setup(HOST, PORTHEX);

    
    //USER DEFINED GLOBALS, SET OFF XML
    
    XML.loadFile("xml/settings.xml");
    
    hex.width=400;
    hex.height=300;
    hex.x=XML.getValue("HEX:X:CURRENT", ofGetWidth()/2);
    hex.y=XML.getValue("HEX:Y:CURRENT", ofGetHeight()/2);
    ringNumber=XML.getValue("RING:NUMBER:CURRENT", 5);
    ringWidth=XML.getValue("RING:WIDTH:CURRENT", 20);
    

    //POPULATE VECTORS FOR THE HEXAGON
    ofPoint coords;
    ofVec2f coordsDot;
    coords.x=hex.x-hex.width*.5;
    coords.y=hex.y;
    hexPoints.push_back(coords);
    
    coords.x=hex.x-hex.width*.4;
    coords.y=hex.y-hex.height*.5;
    hexPoints.push_back(coords);
    
    coords.x=hex.x+hex.width*.4;
    coords.y=hex.y-hex.height*.5;
    hexPoints.push_back(coords);
    
    coords.x=hex.x+hex.width*.5;
    coords.y=hex.y;
    hexPoints.push_back(coords);
    
    coords.x=hex.x+hex.width*.4;
    coords.y=hex.y+hex.height*.5;
    hexPoints.push_back(coords);

    coords.x=hex.x-hex.width*.4;
    coords.y=hex.y+hex.height*.5;
    hexPoints.push_back(coords);

    baseHex.addVertices(hexPoints);
    baseHex.setClosed(true);
    
    
    
    //use the hexPoints to set up visualplayer's points
    for(int i=0;i<hexPoints.size();i++){
        visualPlayer tempVP;
        float verticalOffset = 100;
        
        ofVec2f handle;
        ofVec2f centerScreen;
        ofVec2f origin;
        
        origin = hexPoints[i];
        
        if (i==1||i==2) {
            centerScreen.set(ofGetWidth()/2, ofGetHeight()/2-verticalOffset);
        }else if(i==4||i==5){
            centerScreen.set(ofGetWidth()/2, ofGetHeight()/2+verticalOffset);
        }else{
            centerScreen.set(ofGetWidth()/2, ofGetHeight()/2);
        }

        ofVec2f centerTopPointVec = origin - centerScreen;
        handle = origin + centerTopPointVec*1.5;
        ofVec2f rotationVector = handle - origin;
        
        tempVP.origin = origin;
        tempVP.handle = handle;
        tempVP.handleDefault = handle;
        
        tempVP.baseLine = rotationVector;
        tempVP.baseLineDefault = rotationVector;
        
        tempVP.playerPos=handle;
        visualPlayers.push_back(tempVP);
        
        visualPlayers[i].setup(i);
        
        oscPlayer newOSC;
        newOSC.setup(i); // create a new oscPlayer
        instruments.push_back(newOSC);
    }
    
    ///CENTER VISUALIZATION
    centerOfAll.set(ofGetWidth()/2, ofGetHeight()/2);
    centerVis.setup(hexPoints, centerOfAll);
    
    ///TEXT VISUALIZER
    newTweets.setup();
    
    
}


//--------------------------------------------------------------
void Hexagon::update(bool bDrawAdmin, bool bMouseMode){
    //STATUS CHECK WHETHER DRAWING ADMIN WINDOW CURRENTLY, ` KEY TOGGLES IN APP
    bAdmin=bDrawAdmin;
    bMouse=bMouseMode;
    
    admin.update();
    
    
    cam.update(bAdmin, bMouseMode, admin.camPos1, admin.camPos2, admin.camScale1, admin.camScale2, admin.camRotation1, admin.camRotation2, admin.cvThreshold, admin.gain1, admin.gain2, admin.gamma1, admin.gamma2, admin.shutter1, admin.shutter2, admin.brightness1, admin.brightness2, admin.contrast1, admin.contrast2, admin.hue1, admin.hue2, visualPlayers, admin.pixelSample);
    
    if(bAdmin||bStart){
        
        //POPULATE VECTORS FOR THE HEXAGON, CIRCLES, DOTS
        
        instruments.clear();
        hex.points=admin.gui.getValueI("HEX:POINTS:CURRENT");
        
        
        for(int i=0;i<visualPlayers.size();i++){
            
            oscPlayer newPlayer;
            newPlayer.setup(i); // create a new oscPlayer
            instruments.push_back(newPlayer);
            
        }
        bStart=false;
    }
    
    else{
        
        
        for(int i=0; i<visualPlayers.size();i++){
            //SEND OSC RING INFORMATION
            instruments[i].playRing(&sender, visualPlayers[i].note);
            if(bMouseMode==true){
                if(cam.shapes[i].inside(ofVec2f(mouseX,mouseY))){
                    visualPlayers[i].playerPos=ofVec2f(mouseX,mouseY);
                    visualPlayers[i].bActive=true;
                }
                else{
                    visualPlayers[i].playerPos=visualPlayers[i].handleDefault;
                }
            }
            else{
                if(cam.blobs[i].active==true){
                        visualPlayers[i].playerPos=cam.blobs[i].center;
                        visualPlayers[i].bActive=true;
                }
                else{
                    visualPlayers[i].bActive=false;

                }
            }
            visualPlayers[i].update();
        }
    }
    
    ///TEXT VISUALIZER
    newTweets.update();
    
    ///CENTER VISUALIZER
    for (int i=0; i<visualPlayers.size(); i++) {
        centerVis.repulsionPoints[i].set(visualPlayers[i].origin - visualPlayers[i].baseLine  * visualPlayers[i].zone.posOffset*0.5);

    }
    centerVis.update();
    

    
}



//--------------------------------------------------------------
void Hexagon::draw(){
    ///CV
    cam.draw(admin.CV);
    
    ///CENTER VIS
    centerVis.draw();

    
    ///PLAYERS
    for(int i=0;i<visualPlayers.size();i++){
        visualPlayers[i].draw();        
    }
    
    ///TEXT VISUALIZER
    newTweets.draw();
    
    ///SYPHON
    tex.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    individualTextureSyphonServer.publishTexture(&tex);
    
    admin.draw(bAdmin);
}



//--------------------------------------------------------------
void Hexagon::keyPressed(int key){
    if(bAdmin){
        admin.keyPressed(key);
    }
    cam.keyPressed(key);
    
}

//--------------------------------------------------------------
void Hexagon::keyReleased(int key){
    

    
}

//--------------------------------------------------------------
void Hexagon::mouseMoved(int x, int y){
    if(bAdmin){
        admin.mouseX=mouseX;
        admin.mouseY=mouseY;
        admin.mouseMoved(x,y);
        cam.mouseX=mouseX;
        cam.mouseY=mouseY;
        cam.mouseMoved(x,y);
    }
    
    
    
    
}

//--------------------------------------------------------------
void Hexagon::mouseDragged(int x, int y, int button){
    if(bAdmin){
        admin.mouseX=mouseX;
        admin.mouseY=mouseY;
        admin.mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------
void Hexagon::mousePressed(int x, int y, int button){
    if(bAdmin){
        admin.mouseX=mouseX;
        admin.mouseY=mouseY;
        admin.mousePressed(x,y,button);
    }
}

//--------------------------------------------------------------
void Hexagon::mouseReleased(int x, int y, int button){
    if(bAdmin){
        admin.mouseX=mouseX;
        admin.mouseY=mouseY;
        admin.mouseReleased(x,y,button);
    }
}

//--------------------------------------------------------------
void Hexagon::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void Hexagon::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void Hexagon::dragEvent(ofDragInfo dragInfo){
    
}