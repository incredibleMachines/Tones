//
//  Camera.cpp
//  Tones
//
//  Created by Incredible Machines on 8/21/13.
//
//

#include "Camera.h"


//--------------------------------------------------------------
void Camera::setup(int width, int height){
    
    ps3eye.listDevices();
    ps3eye.setDeviceID(2); //for TONES: 2
//    ps3eye.setDesiredFrameRate(30);
	ps3eye.initGrabber(width,height,false);
    
//  BIG TODO: make this work:
//    ps3eye.setAutoGainAndShutter(false);
    
    
//    ps3eye.setFlicker(0);

//    ps3eye.videoSettings();

//    ps3eye.setGain(1);    /* only if auto gain and shutter is off */
//    ps3eye.setShutter(1); /* only if auto gain and shutter is off */
//    ps3eye.setAnchorPoint(0, 0);
//    ps3eye.setAnchorPercent(100.f, 100.f);
//    ps3eye.setBrightness(0.5);
//    ps3eye.setContrast(0.5);
//    ps3eye.setHue(0.575);
//    ps3eye.setGamma(0.5);

//    ps3eye.setFlicker(1); /* 0 - no flicker, 1 - 50hz, 2 - 60hz */
//    ps3eye.setWhiteBalance(4); /* 1 - linear, 2 - indoor, 3 - outdoor, 4 - auto */
//    ps3eye.setDesiredFrameRate(60);

//    ps3eye.setLed(false); /** Turn the LED on/off on pseye **/
}

//--------------------------------------------------------------
bool Camera::update(){
    ps3eye.update();
    
    if(ps3eye.isFrameNew()) return true;
    else return false;
}

//--------------------------------------------------------------
void Camera::draw(int x, int y, int width, int height){
    camWidth = width;
    camHeight = height;
    
    ps3eye.draw(x,y, width, height);
    ofSetColor(255,255,255);
    ofDrawBitmapString("ps3eye fps: "+ofToString(ps3eye.getRealFrameRate()), 20,20);
    
}

//--------------------------------------------------------------
void Camera::drawStage(){
    ps3eye.draw(0,0, ofGetWidth(), ofGetHeight());
    ofSetColor(255,255,255);
    ofDrawBitmapString("ps3eye fps: "+ofToString(ps3eye.getRealFrameRate()), 20,20);
}

//--------------------------------------------------------------
unsigned char * Camera::getPixels(){
    return ps3eye.getPixels();

}


//--------------------------------------------------------------
void Camera::printCurrentSettings(){
    cout<<"--------------------------"<<endl;
    cout<<"current ps3eye settings: "<<endl;
    cout<<"ps3eye gain: "<<ps3eye.getGain()<<endl;
    cout<<"ps3eye shutter: "<<ps3eye.getShutter()<<endl;
    cout<<"ps3eye contrast: "<<ps3eye.getContrast()<<endl;
    cout<<"ps3eye brightness: "<<ps3eye.getBrightness()<<endl;
    cout<<"ps3eye gamma: "<<ps3eye.getGamma()<<endl;
    cout<<"ps3eye hue: "<<ps3eye.getHue()<<endl;
    cout<<"--------------------------"<<endl;
}