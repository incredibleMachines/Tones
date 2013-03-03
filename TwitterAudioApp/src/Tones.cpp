#include "Tones.h"

//--------------------------------------------------------------
void TwitterTones::setup(){
    
    
    ofBackground(255,255,33);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    
    twitter.setup();
    
    
    
    
}

//--------------------------------------------------------------
void TwitterTones::update(){
   
    twitter.update();

}

//--------------------------------------------------------------
void TwitterTones::draw(){
    ofSetColor(30,30,30);
    ofDrawBitmapString("OSC Listener to send FILE Path to Ableton", 20, 20);

}


//--------------------------------------------------------------
void TwitterTones::keyPressed(int key){

    switch (key) {
        case ' ':
            cout << "pressed" <<endl;
            
            
            twitter.sendToPlayer();
            //twitter.getAudioVoices();
            
            break;
            
    }

}

//--------------------------------------------------------------
void TwitterTones::keyReleased(int key){}

//--------------------------------------------------------------
void TwitterTones::mouseMoved(int x, int y){}

//--------------------------------------------------------------
void TwitterTones::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void TwitterTones::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void TwitterTones::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void TwitterTones::windowResized(int w, int h){}

//--------------------------------------------------------------
void TwitterTones::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void TwitterTones::dragEvent(ofDragInfo dragInfo){}