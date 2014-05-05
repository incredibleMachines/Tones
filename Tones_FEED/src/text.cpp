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
        
    tweetText.init("Arial_Rounded_Bold.ttf", 11);
    userText.init("Arial_Rounded_Bold.ttf", 50);
    tweetText.wrapTextX(500);
    userText.wrapTextX(200);
    
    tweetText.setColor(20, 40, 80, 255);
    userText.setColor(240, 80, 80, 255);
    
    tweetString = "Integer ultrices ipsum vitae sapien auctor ut tempus erat imperdiet. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis metus.";
    userString = "No User Yet.";
    timer=ofGetElapsedTimeMillis();
    
    
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
    
    tweetText.wrapTextX(400);
    
    ofPushStyle();
    tweetText.setColor(240,235,200,255);
    userText.setColor(200, 80, 80, 255);
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
    ofTranslate(ofGetWidth()/2 , 100);
    ofRotateZ(0);
    userText.drawCenter(0, 180);
    if(ofGetElapsedTimeMillis()-timer>375){
        
    }
    tweetText.drawCenter(0, 100);
    ofPopMatrix();
    
    

    
}