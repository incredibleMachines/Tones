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
    
    incomingText.setup(PORT);
        
    tweetText.init("Coquette_Regular.ttf", 40);
    userText.init("Coquette_Regular.ttf", 80);
    tweetText.wrapTextX(800);
    userText.wrapTextX(400);
    
    tweetString = "Nothing Yet. Super long bit of text here. Test Test Test Test Test Testing";
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
    
    
    tweetText.wrapTextX(800);
    
    
    //userText.wrapTextArea(400, 400);
}

//--------------------------------------------------------------
void Text::draw(){
    
    
    //font.drawString(tweetText, 100, 100);
    //font.drawString(userText, 100, 400);
    
    tweetText.drawCenter(ofGetWidth()/2, 100);
    userText.drawCenter(ofGetWidth()/2, 500);
    
}