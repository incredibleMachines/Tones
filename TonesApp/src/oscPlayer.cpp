//
//  oscPlayer.cpp
//  Tones
//
//  Created by Incredible Machines on 2/8/13.
//
//

#include "oscPlayer.h"

oscPlayer::oscPlayer(){
    bPlaying = false;
    prevRing=0;
}

void oscPlayer::setup(int _num){
    playerID = ofToString(_num);
}

//-----------------------------------------------
void oscPlayer::play(ofxOscSender * sender, int speed){
    
        //send speed message, NOT CURRENTLY IMPLEMENTED
        ofxOscMessage s;
        s.setAddress("blob" + playerID + "/speed");
        s.addFloatArg(speed);
        sender->sendMessage( s );
        
}


//-----------------------------------------------
void oscPlayer::playRing (ofxOscSender * sender, int ring){
    if(ring!=prevRing){
        
        //SEND CURRENT NOTE ON MESSAGE
        ofxOscMessage m;
        m.setAddress("blob" + playerID + "/ring" + ofToString(ring));
        m.addFloatArg(1);
        sender->sendMessage( m );

        //SEND PREVIOUS NOTE OFF MESSAGE
        if (bPlaying) {
            ofxOscMessage n;
            n.setAddress("blob" + playerID + "/ring" + ofToString(prevRing));
            n.addFloatArg(0);
            sender->sendMessage( n );
        }
        
        prevRing=ring;
        bPlaying=true;
    }
}









