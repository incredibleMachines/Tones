//
//  Bullseye.cpp
//  Tones
//
//  Created by Incredible Machines on 8/23/13.
//
/*  Bullseye class contains 
 *
 *  - all treated graphics shown on the live "stage".
 *  - evaluation of blob location in polygons is done here
 *  - OSC SENDING when a note gets triggered by blob location
 *  - OSC RECEIVING when a tweet is send from the Node server
 */

//

#include "Bullseye.h"
#include "Tones.h"

//--------------------------------------------------------------
void Bullseye::setup(){
    
    //-- bullseye stuff
    translucentMode = false;
    
    int startX = ofGetWidth()/2;
    int startY = ofGetHeight()/2;
    innerRadius = 116;
    radius = 71;
    for(int j=0; j<6; j++){         //-- how many rings (notes in each slice)
        for(int i=0; i<6; i++){     //-- how many slices of pie (instruments)

            ofPolyline thisLine;
            Line tempZone;
            thisLine.setClosed(true);
            thisLine.arc        (startX, startY, innerRadius+(j-1)*radius+radius,   innerRadius+(j-1)*radius+radius,  i*60,    60+i*60, 120);  //outer curve
            thisLine.arcNegative(startX, startY, innerRadius+(j-1)*radius,   innerRadius+(j-1)*radius,      60+i*60, i*60,    120);  //inner curve
            thisLine.simplify();
            tempZone.polyline=thisLine;
            tempZone.zone=i;
            tempZone.ring=j;
            tempZone.active=false;
            tempZone.noteOnSent = false;
            tempZone.noteOffSent = true;
//            tempZone.lastRing = j;
//            tempZone.lastZone = i;
            lines.push_back(tempZone);
        }
    }
    
    //-- tweet stuff
//    tweetText.init("PTS55F.ttf",12);
//    userText.init("PTS55F.ttf", 12);
    tweetText.init("HelveticaNeueCondensedBold.ttf",12);
    userText.init("HelveticaNeueCondensedBold.ttf", 12);
    currentTweet = "this is a one hundred and forty character tweet. it looks pretty good, and is exactly 140 characters long. one-hundred and forty i do say!!!MMMMM MMMMMMMM MMMMMM.";
    currentUser = "@MMMMMMMMMMMMMM";
    
    bgImg.loadImage("bg/background.png");
    
    //-- osc
    osc.setup();
    loadImages();
}

//--------------------------------------------------------------
void Bullseye::update(){
    pts = ((Tones *)ofGetAppPtr())->pts; //update vector of all current points (blob positions)
    
    if(osc.update()){ //returns true if tweet has arrived
        string incomingTweet = osc.getTweet();
        string incomingUser = osc.getUser();
        currentTweet = incomingTweet;
        currentUser = incomingUser;
        cout<<"INCOMING TWEET: "<<currentTweet<<endl;
        cout<<"INCOMING USER: "<<currentUser<<endl;
    }
}

//--------------------------------------------------------------
void Bullseye::draw(){
    ofSetColor(255);
    

    
    ofFill();
    
        if(translucentMode){ //see the camera behind the design
            ofSetColor(255,0);
            bgImg.draw(0,0,ofGetWidth(),ofGetHeight());

        } else {
            
            bgImg.draw(0,0,ofGetWidth(),ofGetHeight());
        }

    
    for(int i=0; i<lines.size(); i++){ //go through all polylines

        vector <ofPoint> vertices;
        vertices = lines[i].polyline.getVertices(); //get all vertices from this poly
        

        
        ofSetColor(255,0);
        
        
        //cout<<pts.size()<<endl;
        bool inside=false;
        for(int j=0; j<pts.size(); j++){ //go through all current points (closest on blobs)
            if(ofInsidePoly(pts[j], vertices)){ //check if any are inside poly
                //cout<<"BLOB: "<<j<<"  is INSIDE POLY: "<< i <<endl; //--- sanity check
                lines[i].active=true;

                for(int k=0;k<lines.size();k++){
                    if(lines[k].active==true){
                        if(lines[k].zone==lines[i].zone){
                            if(lines[i].ring>=0){
                                if(lines[k].ring<lines[i].ring){
                                    lines[i].active=false;
                                }
                                else if(lines[i].ring<lines[k].ring){
                                    lines[k].active=false;
                                }
                            }
                            else{
                                lines[i+6].active=true;
                                lines[k].active=false;
                            }
                        }
                    }
                }
                inside=true;
            }
        }
        
        if(inside==false){
            lines[i].active=false;
        }
            
    }
    
    for(int i=0; i<lines.size(); i++){ //go through all polylines
        if(lines[i].active==true){
            
            int instrumentID = lines[i].zone; //6 instruments (slices) of the bullseye
            int note = lines[i].ring; //5 ring slices per instrument

            if(!lines[i].noteOnSent){
                osc.sendNoteOn(instrumentID, note); //send the note
                //osc.sendNoteOff(lines[i].lastZone, lines[i].lastRing);
                
                //lines[i].lastZone = lines[i].zone;
                //lines[i].lastRing = lines[i].ring;
                
                lines[i].noteOnSent = true;
                lines[i].noteOffSent = false;
            }
            
            ofSetColor(255);  //make this segment white
            ofFill();
            //img.getTextureReference().bind();
            if(i>5 && i < 30){
                //convert all polys into shapes (in order to Fill() )
//                ofBeginShape();
//                for( int j = 0; j < lines[i].polyline.getVertices().size(); j++) {
//                    ofVertex(lines[i].polyline.getVertices().at(j).x, lines[i].polyline.getVertices().at(j).y);
//                }
//                ofEndShape();
                highlights[i%6][(i-6)/6].draw(0,0);
            }
            
        } else { // zone is NOT ACTIVE
            int instrumentID = lines[i].zone; //6 instruments (slices) of the bullseye
            int note = lines[i].ring; //5 ring slices per instrument
            if(!lines[i].noteOffSent){
                osc.sendNoteOff(lines[i].zone, lines[i].ring);
                lines[i].noteOffSent = true;
                lines[i].noteOnSent = false;
            }
        }
    
    }
    for(int j=0;j<pts.size();j++){
        ofSetColor(255,0,0);
        ofEllipse(pts[j].x,pts[j].y,20,20);
    }

    
    tweetText.setText(currentTweet);
    tweetText.setColor(255, 255, 255, 255);
    tweetText.wrapTextX(innerRadius*2-30);
    tweetText.drawCenter(ofGetWidth()/2,ofGetHeight()/2-55);


    userText.setText(currentUser);
    userText.setColor(0, 255, 255, 255);
    userText.wrapTextX(innerRadius*2-30);
    userText.drawCenter(ofGetWidth()/2,ofGetHeight()/2-90);
    
}

//--------------------------------------------------------------
void Bullseye::updateTweetCopy(){
    
    
    
}

//--------------------------------------------------------------
void Bullseye::toggleTranslucentMode(){

    translucentMode = !translucentMode;
    
}

//--------------------------------------------------------------
void Bullseye::loadImages(){
    for (int i=0;i<6;i++){
        vector<ofImage> images;
        for (int j=1;j<5;j++) {
            ofImage imageLoader;
            string imagePath="bg/"+ofToString(i)+"_"+ofToString(j)+".png";
            cout<<imagePath<<endl;
            imageLoader.loadImage(imagePath);
            images.push_back(imageLoader);
        }
        highlights.push_back(images);
    }
}