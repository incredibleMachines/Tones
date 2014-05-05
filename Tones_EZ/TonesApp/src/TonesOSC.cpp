//
//  Bullseye.cpp
//  Tones
//
//  Created by Incredible Machines on 8/23/13.
//
//

#include "TonesOSC.h"


//--------------------------------------------------------------
void TonesOSC::setup(){
    sender.setup(HOST, PORTSEND);
    receiver.setup(PORTRECEIVE);
}

//--------------------------------------------------------------
bool TonesOSC::update(){
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/tweet"){
            incomingTweet = m.getArgAsString(0);
            incomingUser = m.getArgAsString(1);
//            cout<<"INCOMING TWEET: "<<incomingTweet<<endl;
//            cout<<"INCOMING USER: "<<incomingUser<<endl;
		}
		// check for mouse button message
		else if(m.getAddress() == "/user"){
            
            cout<<"INCOMING USER: "<<m.getArgAsString(0)<<endl;
		} else {
            string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
            }
            cout<<"INCOMING OSC:: "<<endl;
            cout<<msg_string<<endl;
        }
    }
    
    if(incomingTweet.length()>0){
        return true;
        
    } else return false;
}

//--------------------------------------------------------------
//void TonesOSC::sendNote(int instrument, int ring){ //"ring" = note
//
//
//    int inst = instrument;
//    int note = ring;
//    
//    if(note!=prevRing || inst != prevInst){
//        
//        //SEND CURRENT NOTE ON MESSAGE
//        ofxOscMessage m;
//        m.setAddress("blob" + ofToString(inst) + "/ring" + ofToString(note));
//        m.addFloatArg(1);
//        sender.sendMessage( m );
//        
//        //SEND PREVIOUS NOTE OFF MESSAGE
//        if (bPlaying) {
//            ofxOscMessage n;
//            n.setAddress("blob" + ofToString(prevInst) + "/ring" + ofToString(prevRing));
//            n.addFloatArg(0);
//            sender.sendMessage( n );
//        }
//        
//        prevRing=note;
//        prevInst=inst;
//        bPlaying=true;
//    }
//}

//--------------------------------------------------------------
void TonesOSC::sendNoteOn(int instrument, int ring){ //"ring" = note

    
    int inst = instrument;
    int note = ring;
        cout<<"NOTE  ON: inst-"<<ofToString(inst)<<" note-"<<ofToString(note)<<endl;//    
//    if(note!=prevRing || inst != prevInst){
    
        //SEND CURRENT NOTE ON MESSAGE
        ofxOscMessage m;
        m.setAddress("blob" + ofToString(inst) + "/ring" + ofToString(note));
        m.addFloatArg(1);
        sender.sendMessage( m );
        
//        //SEND PREVIOUS NOTE OFF MESSAGE
//        if (bPlaying) {
//            ofxOscMessage n;
//            n.setAddress("blob" + ofToString(prevInst) + "/ring" + ofToString(prevRing));
//            n.addFloatArg(0);
//            sender.sendMessage( n );
//        }
//        
//        prevRing=note;
//        prevInst=inst;
//        bPlaying=true;
//    }
}

//--------------------------------------------------------------
void TonesOSC::sendNoteOff(int instrument, int ring){ //"ring" = note

    
    int inst = instrument;
    int note = ring;
    cout<<"NOTE OFF: inst-"<<ofToString(inst)<<" note-"<<ofToString(note)<<endl;    
//    if(note!=prevRing || inst != prevInst){
//        
        //SEND CURRENT NOTE ON MESSAGE
        ofxOscMessage m;
        m.setAddress("blob" + ofToString(inst) + "/ring" + ofToString(note));
        m.addFloatArg(0);
        sender.sendMessage( m );
    
//        //SEND PREVIOUS NOTE OFF MESSAGE
////        if (bPlaying) {
//            ofxOscMessage n;
//            n.setAddress("blob" + ofToString(inst) + "/ring" + ofToString(note));
//            n.addFloatArg(0);
//            sender.sendMessage( n );
////        }
//        
//        prevRing=note;
//        prevInst=inst;
//        bPlaying=true;
//    }
}

//--------------------------------------------------------------
string TonesOSC::getTweet(){
    string tweetToShow = incomingTweet;
    incomingTweet = "";
    return tweetToShow;
}

string TonesOSC::getUser(){
    string userToShow = "@"+incomingUser;
    incomingUser = "";
    return userToShow;
}