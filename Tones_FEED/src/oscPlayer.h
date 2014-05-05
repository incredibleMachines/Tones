//
//  oscPlayer.h
//  Tones
//
//  Created by Incredible Machines on 2/8/13.
//
//

#ifndef oscPlayer_H
#define oscPlayer_H

#include <iostream>
#include "ofMain.h"
#include "ofxOsc.h"


class oscPlayer {
    
public:

    oscPlayer();
    
    void setup(int _num);
    
    void playRing (ofxOscSender * sender, int ring);
    void play(ofxOscSender * sender, int speed);
    void stop(ofxOscSender * sender);
    
    /// messages
    string  playerID;
    bool    bPlaying;
//    bool bNoteOn;
    int prevRing;
 

};

#endif
