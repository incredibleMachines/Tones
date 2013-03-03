#include "Tones.h"

//--------------------------------------------------------------
void TwitterTones::setup(){
    
    
    ofBackground(33,33,255);
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
    
    ofDrawBitmapString("Twitter Checker Audio Creation and Storage.", 20, 20);

}


//--------------------------------------------------------------
void TwitterTones::keyPressed(int key){

    switch (key) {
        case ' ':
            cout << "pressed" <<endl;
            
            
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