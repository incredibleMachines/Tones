//
//  Camera.h
//  Tones
//
//  Created by Incredible Machines on 8/21/13.
//
//

#pragma once
#include "ofMain.h"
#include "ofxMacamPs3Eye.h"


class Camera{
    
    public:
        void setup(int width, int height);
        bool update();
        void draw(int x, int y, int width, int height);
        void drawStage();
        void saveBackgroundCaptureImg();
        void printCurrentSettings();
        unsigned char * getPixels();
        
        ofxMacamPs3Eye ps3eye;
        int         camWidth;
        int         camHeight;
};