//
//  TonesOSC.h
//  Tones
//
//  Created by Incredible Machines on 8/23/13.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORTSEND 8500
#define PORTRECEIVE 7002
#define ABLETONRECEIVE 9000

class TonesOSC{
    
public:
    void setup();
    bool update();
    void sendNote(int instrument, int note);
        void sendNoteOn(int instrument, int note);
        void sendNoteOff(int instrument, int note);
    string getTweet();
    string getUser();
    
    bool    bPlaying;
    int     prevRing;
    int     prevInst;
    
   
    
    ofxOscSender        sender;
    ofxOscReceiver      receiver;
    
    ofxOscReceiver abletonReceiver;
    string incomingMidi;
    
    string addrCheck; //incoming address
    
    bool beatOn;
    bool instOn[6]; //instrument ons
    
    string incomingTweet;
    string incomingUser;

};