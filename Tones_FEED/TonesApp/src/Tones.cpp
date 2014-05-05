#include "Tones.h"

//--------------------------------------------------------------
void Tones::setup(){
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    ofEnableAlphaBlending();
    ofSetCircleResolution(60);
    hex.setup();
    
    //TURN ON TEST MODE
    bTestMode=false;
    bMouseMode=true;
    
    if(bTestMode){
        timer=ofGetElapsedTimeMillis();
    }
}

//--------------------------------------------------------------
void Tones::update(){
    hex.update(bDrawAdmin,bMouseMode);
    

}

//--------------------------------------------------------------
void Tones::draw(){
    ofSetLineWidth(2);
//    ofCircle(ofGetWidth()/2, ofGetHeight()/2, 5);
//    ofDrawBitmapString(ofToString(ofGetFrameRate()),ofGetWidth()/4,ofGetHeight()/4); ///Draw framerate
    hex.draw();

}

//--------------------------------------------------------------
void Tones::keyPressed(int key){
    if(bDrawAdmin){
        hex.keyPressed(key);
    }
    switch(key){
        case '`':
        case '~':
            bDrawAdmin=!bDrawAdmin;
            break;
    }
    
    hex.keyPressed(key);
    
//    if (key=='1') {
//        hex.visualPlayers[0].zones[0].update(0, 0);
//    }
//    if (key=='2') {
//        hex.visualPlayers[0].zones[1].update(1, 1);
//    }
//    if (key=='3') {
//        hex.visualPlayers[0].zones[2].update(2, 2);
//    }
//    if (key=='4') {
//        hex.visualPlayers[0].zones[3].update(3, 3);
//    }
//    if (key=='5') {
//        hex.visualPlayers[0].zones[4].update(4, 4);
//    }


}

//--------------------------------------------------------------
void Tones::keyReleased(int key){
    
    hex.keyReleased(key);

}

//--------------------------------------------------------------
void Tones::mouseMoved(int x, int y){
        hex.mouseX=mouseX;
        hex.mouseY=mouseY;
        hex.mouseMoved(x,y);
}

//--------------------------------------------------------------
void Tones::mouseDragged(int x, int y, int button){
        hex.mouseX=mouseX;
        hex.mouseY=mouseY;
        hex.mouseDragged(x,y,button);
    
}

//--------------------------------------------------------------
void Tones::mousePressed(int x, int y, int button){

        hex.mouseX=mouseX;
        hex.mouseY=mouseY;
        hex.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void Tones::mouseReleased(int x, int y, int button){
        hex.mouseX=mouseX;
        hex.mouseY=mouseY;
        hex.mouseReleased(x,y,button);
    
}

//--------------------------------------------------------------
void Tones::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void Tones::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void Tones::dragEvent(ofDragInfo dragInfo){
    
}