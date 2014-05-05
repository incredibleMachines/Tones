//
//  Hexagon.h
//  Tones
//
//  Created by IncredibleMachines on 2/8/13.
//
//

#pragma once

#include "ofMain.h"
#include "oscPlayer.h"
#include "ofxOsc.h"
#include "ofxControlPanel.h"
#include "AdminWindow.h"
#include "ofxSyphon.h"
#include "CameraCV.h"
#include "visualPlayer.h"
#include "centerVisual.h"
#include "text.h"

#include <GLUT/GLUT.h>

///OSC definitions
#define HOST "localhost"
#define PORTHEX 8500



class Hexagon : public ofBaseApp{
public:
    
    void setup();
    void update(bool bDrawAdmin, bool bMouseMode);
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    class hexShape{
    public:
        float width;
        float height;
        int x;
        int y;
        int points;
    };
    
    ///Globals
    ofxXmlSettings XML;
    AdminWindow admin;
    bool bAdmin;
    bool bMouse;
    bool bStart;
    int color[6] = {0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x00ffff};
    
    
    ///Visuals
    vector<visualPlayer> visualPlayers;
    centerVisual centerVis;
    vector<ofPoint> hexPoints;
    hexShape hex;
    ofPolyline baseHex;
    ofPoint centerOfAll;
    
    int ringNumber;
    float ringWidth;
    
    ///OSC Communication
    vector <oscPlayer>  instruments;
    ofxOscSender        sender;
    
    ///Syphon
    ofTexture tex;
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
    
    ///CV
    CameraCV cam;
    
    ///Text
    Text newTweets;
    
    
    

};
