#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    ofSetBackgroundColor(50);
    
    newTweets.setup();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    newTweets.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    newTweets.draw();
    
}

