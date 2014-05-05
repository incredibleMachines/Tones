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
	gui.setup("#Tones Setup", 0, 0, ofGetWidth(), ofGetHeight());
	gui.addPanel("Hexagon Size and Position", 1, false);
    gui.addPanel("Player Circles Size and Position", 2, false);
	gui.addPanel("CV Threshold and Alignment", 3, false);
    
    //HEXAGON PANEL
    
    gui.setWhichPanel("Hexagon Size and Position");
    gui.addLabel("Hit R to restore Global Defaults");
    gui.addLabel("Use ARROW keys to move hex center 1px");
    gui.addLabel("Use -/+ to Scale hex symmetrically");
    gui.addSlider("width", "HEX:WIDTH:CURRENT", 200, ofGetWidth()/6, ofGetWidth()/2, true);
    gui.addSlider("height", "HEX:HEIGHT:CURRENT", 200, ofGetHeight()/8, ofGetHeight()/2, true);
    gui.addSlider("hex center x", "HEX:X:CURRENT", ofGetWidth()/2, ofGetWidth()/4, ofGetWidth()*.75, true);
    gui.addSlider("hex center y", "HEX:Y:CURRENT", ofGetHeight()/2, ofGetHeight()/4, ofGetHeight()*.75, true);
    gui.addSlider("hex points", "HEX:POINTS:CURRENT",6,4,8,true);
    int points=gui.getValueI("HEX:POINTS:CURRENT");
    
    gui.setWhichPanel("Player Circles Size and Position");
    for(int i=0; i<points;i++){
        string point=ofToString(i);

        gui.addSlider("origin X"+point, "HEX:SHAPE"+point+":ORIGINX:CURRENT", ofGetWidth()/2, 0, ofGetWidth(), true);
        gui.addSlider("origin Y"+point, "HEX:SHAPE"+point+":ORIGINY:CURRENT", ofGetHeight()/2, 0, ofGetHeight(), true);
        gui.addSlider("handle X"+point, "HEX:SHAPE"+point+":HANDLEX:CURRENT", 100, 0, ofGetWidth(), true);
        gui.addSlider("handle Y"+point, "HEX:SHAPE"+point+":HANDLEY:CURRENT", 100, 0, ofGetHeight(), true);

}
    
    gui.setWhichPanel("CV Threshold and Alignment");
    gui.addLabel("Hit R to restore Global Defaults");
    gui.addLabel("Hit SPACE to reset background");
    gui.addLabel("Use ARROW keys for 1px adjustments to Img1");
    gui.addLabel("SHIFT+ARROW keys for adjustments to Img2");
    gui.addLabel("Use -/= to Scale Img1 symmetrically");
    gui.addLabel("Use _/+ to Scale Img2 symmetrically");
    gui.addToggle("CV draw to screen", "CAM1:DRAW:CURRENT", 0);
    gui.addToggle("CV draw contours to screen", "CAM1:CONTOUR:CURRENT", 0);
    gui.addSlider("CV Threshold", "CV:THRESHOLD:CURRENT", 20, 0, 255, true);
    gui.addSlider("Pixel Sample Size", "CV:SIZE:CURRENT", 25, 1, 100, true);

    gui.setWhichColumn(1);
    gui.addSlider("CV 1 x scale %", "CAM1:X:SCALE:CURRENT", 100, 50, 300, true);
    gui.addSlider("CV 1 y scale %", "CAM1:Y:SCALE:CURRENT", 100, 50, 300, true);
    gui.addSlider("CV 1 x align", "CAM1:X:POS:CURRENT", 0, -ofGetWidth()/2, ofGetWidth(), true);
    gui.addSlider("CV 1 y align", "CAM1:Y:POS:CURRENT", 0, -ofGetHeight()/2, ofGetHeight(), true);
    gui.addSlider("CV 1 rotate", "CAM1:ROTATE:CURRENT", 0, -180, 180, true);
    gui.addSlider("CV 2 x scale %", "CAM2:X:SCALE:CURRENT", 100, 50, 300, true);
    gui.addSlider("CV 2 y scale %", "CAM2:Y:SCALE:CURRENT", 100, 50, 300, true);
    gui.addSlider("CV 2 x align", "CAM2:X:POS:CURRENT", 0, -ofGetWidth()/2, ofGetWidth(), true);
    gui.addSlider("CV 2 y align", "CAM2:Y:POS:CURRENT", 0, -ofGetHeight()/2, ofGetHeight(), true);
    gui.addSlider("CV 2 rotate", "CAM2:ROTATE:CURRENT", 0, -180, 180, true);

    
    gui.setWhichColumn(2);
    gui.addSlider("Camera 1 Gain", "CAM1:GAIN:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Shutter", "CAM1:SHUTTER:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Gamma", "CAM1:GAMMA:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Brightness", "CAM1:BRIGHTNESS:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Contrast", "CAM1:CONTRAST:CURRENT",0.5, 0, 1.0, false);
    gui.addSlider("Camera 1 Hue", "CAM1:HUE:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Gain", "CAM2:GAIN:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Shutter", "CAM2:SHUTTER:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Gamma", "CAM2:GAMMA:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Brightness", "CAM2:BRIGHTNESS:CURRENT", 0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Contrast", "CAM2:CONTRAST:CURRENT",0.5, 0, 1.0, false);
    gui.addSlider("Camera 2 Hue", "CAM2:HUE:CURRENT", 0.5, 0, 1.0, false);
    
    gui.loadSettings("xml/settings.xml");
}

//--------------------------------------------------------------
void AdminWindow::update(){
    gui.update();
    if(gui.getCurrentPanelName()=="CV Threshold and Alignment"){
        int draw=gui.getValueF("CAM1:DRAW:CURRENT",0);
        int contour=gui.getValueF("CAM1:CONTOUR:CURRENT",0);
        if(draw==1&&contour==0) {
            CV=1;
        }
        else if(draw==1&&contour==1 ) {
            CV=2;
        }
        else if(draw==0&&contour==1) {
            CV=3;
        }
        else{
            CV=0;
        }
    }
    else{
        CV=0;
    }
    camPos1.x=gui.getValueF("CAM1:X:POS:CURRENT",0);
    camPos1.y=gui.getValueF("CAM1:Y:POS:CURRENT",0);
    camScale1.x=gui.getValueF("CAM1:X:SCALE:CURRENT",0);
    camScale1.y=gui.getValueF("CAM1:Y:SCALE:CURRENT",0);
    camRotation1=gui.getValueF("CAM1:ROTATE:CURRENT",0);
    camPos2.x=gui.getValueF("CAM2:X:POS:CURRENT",0);
    camPos2.y=gui.getValueF("CAM2:Y:POS:CURRENT",0);
    camScale2.x=gui.getValueF("CAM2:X:SCALE:CURRENT",0);
    camScale2.y=gui.getValueF("CAM2:Y:SCALE:CURRENT",0);
    camRotation2=gui.getValueF("CAM2:ROTATE:CURRENT",0);
    
    hexPos.x=gui.getValueF("HEX:X:CURRENT",0);
    hexPos.y=gui.getValueF("HEX:Y:CURRENT",0);
    hexScale.x=gui.getValueF("HEX:WIDTH:CURRENT",0);
    hexScale.y=gui.getValueF("HEX:HEIGHT:CURRENT",0);
    
    cvThreshold=gui.getValueI("CV:THRESHOLD:CURRENT",0);
    
    gain1=gui.getValueF("CAM1:GAIN:CURRENT");
    gamma1=gui.getValueF("CAM1:GAMMA:CURRENT");
    shutter1=gui.getValueF("CAM1:SHUTTER:CURRENT");
    brightness1=gui.getValueF("CAM1:BRIGHTNESS:CURRENT");
    contrast1=gui.getValueF("CAM1:CONTRAST:CURRENT");
    hue1=gui.getValueF("CAM1:HUE:CURRENT");
    gain2=gui.getValueF("CAM2:GAIN:CURRENT");
    shutter2=gui.getValueF("CAM2:SHUTTER:CURRENT");
    brightness2=gui.getValueF("CAM2:BRIGHTNESS:CURRENT");
    contrast2=gui.getValueF("CAM2:CONTRAST:CURRENT");
    hue2=gui.getValueF("CAM2:HUE:CURRENT");
    gamma2=gui.getValueF("CAM2:GAMMA:CURRENT");
    
    pixelSample=gui.getValueI("CV:PIXELS:CURRENT");
    
}

//--------------------------------------------------------------
void AdminWindow::draw(bool bDrawAdmin){
    if(bDrawAdmin){
        gui.draw();
    }
}

//--------------------------------------------------------------
void AdminWindow::keyPressed  (int key){
    
	bool control_panel_ate_key = gui.keyPressed( key );
    
    if(gui.getCurrentPanelName()=="CV Threshold and Alignment"){
            switch (key){
                case 'R':
                    defaults();
                    break;
                case OF_KEY_UP:
                    if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
                        gui.setValueF("CAM2:Y:POS:CURRENT", camPos2.y-1);
                    }
                    else{
                        gui.setValueF("CAM1:Y:POS:CURRENT", camPos1.y-1);
                    }
                    break;
                case OF_KEY_DOWN:
                    if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
                        gui.setValueF("CAM2:Y:POS:CURRENT", camPos2.y+1);
                    }
                    else{
                        gui.setValueF("CAM1:Y:POS:CURRENT", camPos1.y+1);
                    }
                    break;
                case OF_KEY_RIGHT:
                    if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
                        gui.setValueF("CAM2:X:POS:CURRENT", camPos2.x+1);
                    }
                    else{
                        gui.setValueF("CAM1:X:POS:CURRENT", camPos1.x+1);
                    }
                    break;
                case OF_KEY_LEFT:
                    if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
                        gui.setValueF("CAM2:X:POS:CURRENT", camPos2.x-1);
                    }
                    else{
                        gui.setValueF("CAM1:X:POS:CURRENT", camPos1.x-1);
                    }
                    break;
                case '=':
                    gui.setValueF("CAM1:X:SCALE:CURRENT", camScale1.x+.5);
                    gui.setValueF("CAM1:Y:SCALE:CURRENT", camScale1.y+.5);
                    break;
                case '+':
                    gui.setValueF("CAM2:X:SCALE:CURRENT", camScale2.x+.5);
                    gui.setValueF("CAM2:Y:SCALE:CURRENT", camScale2.y+.5);
                    break;
                case '-':
                    gui.setValueF("CAM1:X:SCALE:CURRENT", camScale1.x-.5);
                    gui.setValueF("CAM1:Y:SCALE:CURRENT", camScale1.y-.5);
                    break;
                case '_':
                    gui.setValueF("CAM2:X:SCALE:CURRENT", camScale2.x-.5);
                    gui.setValueF("CAM2:Y:SCALE:CURRENT", camScale2.y-.5);
                    break;
        }
    }
    
    else if(gui.getCurrentPanelName()=="Hexagon Size and Position"){
        switch (key){
            case 'R':
                defaults();
                break;
            case OF_KEY_UP:
                gui.setValueF("HEX:Y:CURRENT", hexPos.y-1);
                break;
            case OF_KEY_DOWN:
                gui.setValueF("HEX:Y:CURRENT", hexPos.y+1);
                break;
            case OF_KEY_RIGHT:
                gui.setValueF("HEX:X:CURRENT", hexPos.x+1);
                break;
            case OF_KEY_LEFT:
                gui.setValueF("HEX:X:CURRENT", hexPos.x-1);
                break;
            case '=':
            case '+':
                gui.setValueF("HEX:WIDTH:CURRENT", hexScale.x+.5);
                gui.setValueF("HEX:HEIGHT:CURRENT", hexScale.y+.5);
                break;
            case '-':
            case '_':
                gui.setValueF("HEX:WIDTH:CURRENT", hexScale.x-.5);
                gui.setValueF("HEX:HEIGHT:CURRENT", hexScale.y-.5);
                break;
        }
    }
	
}

//--------------------------------------------------------------
void AdminWindow::keyReleased  (int key){
    
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
    
    if(gui.getCurrentPanelName()=="Hexagon Size and Position"){
        float width=XML.getValue("HEX:WIDTH:DEFAULT", 200);
        float height=XML.getValue("HEX:HEIGHT:DEFAULT", 100);
        float x=ofGetWidth()/2;
        float y=ofGetHeight()/2;
        int ringNumber=XML.getValue("RING:NUMBER:DEFAULT", 5);
        float ringWidth=XML.getValue("RING:WIDTH:DEFAULT", 20);
        
        gui.setValueF("HEX:WIDTH:CURRENT", width);
        gui.setValueF("HEX:HEIGHT:CURRENT", height);
        gui.setValueF("HEX:X:CURRENT", x);
        gui.setValueF("HEX:Y:CURRENT", y);
        gui.setValueF("RING:NUMBER:CURRENT", ringNumber);
        gui.setValueF("RING:WIDTH:CURRENT", ringWidth);
    }
    
    else if(gui.getCurrentPanelName()=="Player Circles Size and Position"){

    }
    
    else if(gui.getCurrentPanelName()=="CV Threshold and Alignment"){
        float scalex=XML.getValue("CAM1:X:SCALE:DEFAULT", 100);
        float scaley=XML.getValue("CAM1:Y:SCALE:DEFAULT", 100);
        float x=XML.getValue("CAM1:X:POS:DEFAULT", 0);
        float y=XML.getValue("CAM1:Y:POS:DEFAULT", 0);
        float view=XML.getValue("CAM1:VIEW:DEFAULT", 0);
        float draw=XML.getValue("CAM1:DRAW:DEFAULT", 0);
        float contour=XML.getValue("CAM1:CONTOUR:DEFAULT", 0);
        float rot=XML.getValue("CAM1:ROTATE:DEFAULT", 0);
        float scalex2=XML.getValue("CAM2:X:SCALE:DEFAULT", 100);
        float scaley2=XML.getValue("CAM2:Y:SCALE:DEFAULT", 100);
        float x2=XML.getValue("CAM2:X:POS:DEFAULT", 0);
        float y2=XML.getValue("CAM2:Y:POS:DEFAULT", 0);
        float rot2=XML.getValue("CAM2:ROTATE:DEFAULT", 0);
        int thresh=XML.getValue("CV:THRESHOLD:DEFAULT",0);
        int pixels=XML.getValue("CV:SIZE:CURRENT", 0);
        
        gui.setValueI("CV:THRESHOLD:CURRENT",thresh);
        gui.setValueI("CV:SIZE:CURRENT",pixels);
        gui.setValueF("CAM1:X:SCALE:CURRENT", scalex);
        gui.setValueF("CAM1:Y:SCALE:CURRENT", scaley);
        gui.setValueF("CAM1:X:POS:CURRENT", x);
        gui.setValueF("CAM1:Y:POS:CURRENT", y);
        gui.setValueF("CAM1:VIEW:CURRENT", view);
        gui.setValueF("CAM1:DRAW:CURRENT", view);
        gui.setValueF("CAM1:CONTOUR:CURRENT", view);
        gui.setValueF("CAM1:ROTATE:CURRENT", rot);
        gui.setValueF("CAM2:X:SCALE:CURRENT", scalex);
        gui.setValueF("CAM2:Y:SCALE:CURRENT", scaley);
        gui.setValueF("CAM2:X:POS:CURRENT", x);
        gui.setValueF("CAM2:Y:POS:CURRENT", y);
        gui.setValueF("CAM2:ROTATE:CURRENT", rot);
    }
    
}

