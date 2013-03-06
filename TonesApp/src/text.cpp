//
//  text.cpp
//  textDrawer
//
//  Created by inrediblemachines on 2/27/13.
//
//

#include "text.h"

//--------------------------------------------------------------
void Text::setup(){
    
    incomingText.setup(PORTTEXT);
        
    tweetText.init("Coquette_Regular.ttf", 9);
    userText.init("Coquette_Regular.ttf", 30);
    tweetText.wrapTextX(240);
    userText.wrapTextX(200);
    
    tweetText.setColor(20, 40, 80, 255);
    userText.setColor(20, 40, 80, 255);
    
    tweetString = "Integer ultrices ipsum vitae sapien auctor ut tempus erat imperdiet. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis metus.";
    userString = "No User Yet.";
    
    
}

//--------------------------------------------------------------
void Text::update(){
    
    while (incomingText.hasWaitingMessages()) {
        ofxOscMessage m;
        incomingText.getNextMessage(&m);
        
        if(m.getAddress() == "/tweet"){
            ofDrawBitmapString("GotMessage", 20, 20);
            tweetString= m.getArgAsString(1);
            userString=m.getArgAsString(2);
        }
    }
    
    tweetText.setText(tweetString);
    userText.setText("@"+userString);
    
    //    change all the text colors.
    //    for(int i =0; i<tweetText.words.size(); i++){
    //
    //        tweetText.words[i].color.r=ofRandom(255);
    //        tweetText.words[i].color.g=ofRandom(255);
    //        tweetText.words[i].color.b=ofRandom(255);
    //    }
    
    
    tweetText.wrapTextX(260);
    
    ofPushStyle();
    tweetText.setColor(255,255,255,255);
    userText.setColor(20, 40, 80, 255);
    //userText.setColor(255, 0, 0, 255);
    userText.forceScale(0.3f);
    //userText.wrapTextArea(400, 400;);
    ofPopStyle();
    
}

//--------------------------------------------------------------
void Text::draw(){
    
    
    //font.drawString(tweetText, 100, 100);
    //font.drawString(userText, 100, 400);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2+ ofGetWidth()/12, ofGetHeight()/2);
    ofRotateZ(90);
    userText.drawCenter(0, 155);
    tweetText.drawCenter(0, 100);
    ofPopMatrix();
    
    

    
}