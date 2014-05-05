#pragma once

#include "ofMain.h"
#include "ofxControlPanel.h"
#include "ofxXmlSettings.h"
#include <GLUT/GLUT.h>

class AdminWindow : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void eventsIn(guiCallbackData & data);
    void grabBackgroundEvent(guiCallbackData & data);
    
    void keyPressed  (int key);
    void keyReleased (int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void defaults();
    
    int returnCV();
    
    bool active;
    int CV;
    
    ofxControlPanel gui;
    
    ofTrueTypeFont TTF;
    
    ofxXmlSettings XML;
    
    ofPoint camPos1, camPos2, camScale1, camScale2, hexPos, hexScale;
    float camRotation1, camRotation2;
    float gain1, gain2, shutter1, shutter2, brightness1, brightness2, contrast1, contrast2, hue1, hue2, gamma1, gamma2;
    int cvThreshold, pixelSample;
    
};