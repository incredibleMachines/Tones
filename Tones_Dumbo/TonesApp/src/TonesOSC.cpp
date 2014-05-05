//
//  Bullseye.cpp
//  Tones
//
//  Created by Incredible Machines on 8/23/13.
//
//

#include "ofMain.h"
#include "TonesOSC.h"


//--------------------------------------------------------------
void TonesOSC::setup(){
    sender.setup(HOST, PORTSEND);
    receiver.setup(PORTRECEIVE);
    abletonReceiver.setup(ABLETONRECEIVE);
    
    //pIncomingMidi = new string;
    //*pIncomingMidi = "";
    incomingMidi = "";
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
    
    while(abletonReceiver.hasWaitingMessages()){
        ofxOscMessage m;
		abletonReceiver.getNextMessage(&m);

        string address = m.getAddress();
        int numArgs = m.getNumArgs();
        int arg0 = m.getArgAsInt32(0);
        
        //cout<< "address: " << address << " | numArgs: "<<numArgs<<" | arg0: "<<arg0<<endl;
        
        addrCheck = address.substr(11,2);
        //cout << addrCheck << endl;
        
        if (addrCheck == "9/"){
            //cout<< "got beat | arg0: "<<arg0<<endl;
            beatOn = arg0;
            //cout<<beatOn<<endl;
        }
        
        else { //we got a note on or off
            //reset active timestamps here?
            
            //cout<<"addr: "<<addrCheck<<" | arg0: "<<arg0<<endl;
            if (addrCheck == "11"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                instOn[0] = arg0;
                
            } else if (addrCheck == "12"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                instOn[1] = arg0;
                
            } else if (addrCheck == "13"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                if(arg0 == 1){
                    cout<<ofGetElapsedTimeMillis()<<endl;
                    instOn[2] = true;
                } else {
                    instOn[2] = false;
                }
                
                
            } else if (addrCheck == "14"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                instOn[3] = arg0;
                
            } else if (addrCheck == "15"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                instOn[4] = arg0;
                
            } else if (addrCheck == "16"){
                //cout<< "got inst: "<<addrCheck<<" | arg0: "<<arg0<<endl;
                instOn[5] = arg0;
            }
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
//        cout<<"NOTE  ON: inst-"<<ofToString(inst)<<" note-"<<ofToString(note)<<endl;//    
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
//    cout<<"NOTE OFF: inst-"<<ofToString(inst)<<" note-"<<ofToString(note)<<endl;    
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