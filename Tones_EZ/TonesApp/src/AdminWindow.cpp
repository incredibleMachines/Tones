//
//  AdminWindow.cpp
//  AdminWindow
//
//  Created by IncredibleMachines on 2/13/13.
//
//

#include "AdminWindow.h"

//--------------------------------------------------------------
void AdminWindow::setup(){
    ofxControlPanel::setBackgroundColor(simpleColor(0,0,0, 50));
	ofxControlPanel::setTextColor(simpleColor(240, 50, 50, 255));
	gui.loadFont("fonts/Helvetica.dfont", 8);
    
    gui.setup("TONES EZ ADMIN", 0, 0, ofGetWidth(), 700);
    gui.addPanel("Setup", 0, false);
    gui.setWhichPanel(0);
    //    gui.addSlider("Camera 1 Gain", "CAM1:GAIN:CURRENT", 0.5, 0, 1.0, false);
    //    gui.addSlider("Camera 1 Shutter", "CAM1:SHUTTER:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Gamma", "CAM1:GAMMA", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Brightness", "CAM1:BRIGHTNESS", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Contrast", "CAM1:CONTRAST",0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Hue", "CAM1:HUE", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Threshold", "CAM1:THRESH", 50, 0, 100, false);
    
    
    gui.loadSettings("xml/settings.xml");
}

//--------------------------------------------------------------
void AdminWindow::update(){
    gui.update();
    


    
}

//--------------------------------------------------------------
void AdminWindow::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void AdminWindow::keyPressed  (int key){
	
}

//--------------------------------------------------------------
void AdminWindow::keyReleased  (int key){
    
    switch(key){

    }
    
}

//--------------------------------------------------------------
void AdminWindow::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void AdminWindow::mouseDragged(int x, int y, int button){
	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void AdminWindow::mousePressed(int x, int y, int button){
	gui.mousePressed(x, y, button);
    
}

//--------------------------------------------------------------
void AdminWindow::mouseReleased(int x, int y, int button){
	gui.mouseReleased();
}

//--------------------------------------------------------------
void AdminWindow::defaults(){
    
    
    
    
}

