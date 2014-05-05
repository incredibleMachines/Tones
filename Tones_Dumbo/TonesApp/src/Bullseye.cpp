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
 *  - Visual Styling
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
    innerRadius = 150;
    radius = 67;
    instruments=6;
    vector<ofVec2f> startPoint;
    vector<ofVec2f> endPoint;
    for(int j=0; j<4; j++){         //-- how many notes
        for(int i=0; i<instruments; i++){     //-- how many instruments
            
            if(j==0){
                startPoint.push_back(ofVec2f(ofGetWidth()/2 + (innerRadius) * cos(i*((2*PI)/instruments)),ofGetHeight()/2 + (innerRadius) * sin(i*((2*PI)/instruments))));
                endPoint.push_back(ofVec2f(ofGetWidth()/2 + (innerRadius) * cos((i+1)*((2*PI)/instruments)),ofGetHeight()/2 + (innerRadius) * sin((i+1)*((2*PI)/instruments))));
            }
            
            //            if(j<1){
            //            ofPolyline thisLine;
            //            Line tempZone;
            //            thisLine.setClosed(true);
            //            thisLine.arc        (startX, startY, innerRadius+(j-1)*radius+radius,   innerRadius+(j-1)*radius+radius,  i*60,    60+i*60, 120);  //outer curve
            //            thisLine.arcNegative(startX, startY, innerRadius+(j-1)*radius,   innerRadius+(j-1)*radius,      60+i*60, i*60,    120);  //inner curve
            //            thisLine.simplify();
            //            tempZone.polyline=thisLine;
            //            tempZone.zone=i;
            //            tempZone.ring=j;
            //            tempZone.active=false;
            //            tempZone.noteOnSent = false;
            //            tempZone.noteOffSent = true;
            ////            tempZone.lastRing = j;
            ////            tempZone.lastZone = i;
            //            lines.push_back(tempZone);
            //            }
            //
            //            else{
            
            ofPolyline thisLine;
            Line tempZone;
            thisLine.setClosed(true);
            ofVec2f diagonal=endPoint[i]-startPoint[i];
            ofVec2f perp=diagonal.perpendicular();
            thisLine.addVertex(startPoint[i]-perp*j*radius);
            thisLine.addVertex(endPoint[i]-perp*j*radius);
            thisLine.addVertex(endPoint[i]-perp*(j+1)*radius);
            thisLine.addVertex(startPoint[i]-perp*(j+1)*radius);
            thisLine.addVertex(startPoint[i]-perp*j*radius);
            
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
    tweetText.init("HelveticaNeueCondensedBold.ttf",12);
    userText.init("HelveticaNeueCondensedBold.ttf", 12);
    currentTweet = "this is a one hundred and forty character tweet. it looks pretty good, and is exactly 140 characters long. one-hundred and forty i do say!!!MMMMM MMMMMMMM MMMMMM.";
    currentUser = "@MMMMMMMMMMMMMM";
    
    bgImg.loadImage("bg/background.png");
    
    
    //-- osc
    osc.setup();
    loadImages();
    
    /// -- Meshes for each note
    for(int i=0; i<lines.size(); i++){
        ofMesh tempMesh;
        tempMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        tempMesh.setupIndicesAuto();
        meshes.push_back(tempMesh);
    }
    
    //    for(int i=0; i<lines.size(); i++){
    //        meshes[i].addColor(ofColor(255));
    //        meshes[i].addVertex(lines[i].polyline.getCentroid2D());
    //        ofVec2f correctedPos = lines[i].polyline.getVertices().at(0) - lines[i].polyline.getVertices().at(1);
    //        correctedPos.normalize();
    //        for( int j = 0; j < lines[i].polyline.getVertices().size(); j++) {
    //            meshes[i].addColor(ofColor(255,0));
    //
    //            if (j==0) {
    //                meshes[i].addVertex(lines[i].polyline.getVertices().at(j) - correctedPos*(5));
    //            }else if(j==1){
    //                meshes[i].addVertex(lines[i].polyline.getVertices().at(j) + correctedPos*(5 + j));
    //            }else if(j==4){
    //                meshes[i].addVertex(lines[i].polyline.getVertices().at(j) - correctedPos*(5));
    //            }
    //            else{
    //                meshes[i].addVertex(lines[i].polyline.getVertices().at(j));
    //            }
    //        }
    //    }
    
    /// -- Background meshes
    bgMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    bgMesh.addColor(ofColor(20,20,30,255));
    bgMesh.addVertex(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
    for(int i=0; i<13; i++){
        float angle = (TWO_PI/6)*i;
        float x = ofGetWidth()/2 + cos(angle) * 140;
        float y = ofGetWidth()/2 + sin(angle) * 140;
        
        bgMesh.addColor(ofColor(20,20,20,0));
        bgMesh.addVertex(ofVec2f(x,y));
    }
    
    ringMaster.setup();
    bgTex = bgImg.getTextureReference();
    factor = 0;
}

//--------------------------------------------------------------
void Bullseye::update(){
    pts = ((Tones *)ofGetAppPtr())->pts; //update vector of all current points (blob positions)
    
    if(osc.update()){ //returns true if tweet has arrived
        string incomingTweet = osc.getTweet();
        string incomingUser = osc.getUser();
        currentTweet = incomingTweet;
        currentUser = incomingUser;
//        cout<<"INCOMING TWEET: "<<currentTweet<<endl;
//        cout<<"INCOMING USER: "<<currentUser<<endl;
    }
    
    // -- Shading
    shader.load("shaders/shader");
}

//--------------------------------------------------------------
void Bullseye::draw(){
    ofSetColor(255);
    ofFill();
    
    for(int i=0; i<lines.size(); i++){ //go through all polylines
        
        vector <ofPoint> vertices;
        vertices = lines[i].polyline.getVertices(); //get all vertices from this poly
        
        //cout<<pts.size()<<endl;
        bool inside=false;
        for(int j=0; j<pts.size(); j++){ //go through all current points (closest on blobs)
            if(ofInsidePoly(pts[j], vertices)){ //check if any are inside poly
                //cout<<"BLOB: "<<j<<"  is INSIDE POLY: "<< i <<endl; //--- sanity check
                lines[i].active=true;
                for(int k=0;k<lines.size();k++){
                    
                    if(lines[k].active==true){
                        if(lines[k].zone==lines[i].zone){
                            if(lines[k].ring<lines[i].ring){
                                lines[i].active=false;
                            }
                            else if(lines[i].ring<lines[k].ring){
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
                    lines[i].activeTimestamp = ofGetElapsedTimeMillis();
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
        
        /// -- Background
        if(translucentMode){ //see the camera behind the design
            ofSetColor(255,0);
            bgImg.draw(0,0,ofGetWidth(),ofGetHeight());
        } else {
            bgImg.draw(0,0,ofGetWidth(),ofGetHeight());
        }
        
        /// -- Shader
        bool bHaveBeat = osc.beatOn;
        float beatUniform;
        
        if (bHaveBeat) {
            beatUniform = 1.0;
        }else{
            beatUniform = 0.0;
        }
        
        ofSetColor(255);
        shader.begin();
        shader.setUniformTexture("tex", bgTex, 0);
        shader.setUniform1f("beat", beatUniform);
        shader.setUniform1f("time", ofGetElapsedTimef()*50);
        bgTex.draw(0,0);
        shader.end();
        
        
        
        if(translucentMode){ //see the camera behind the design
            ofSetColor(255,0);
            bgImg.draw(0,0,ofGetWidth(),ofGetHeight());
        } else {
            /// -- ringmaster
            ringMaster.update(pts, osc);
            ringMaster.draw();
            bgMesh.draw();
        }
        
        
        /// -- Uncomment to draw all polys
        //    for(int i=0; i<lines.size(); i++){ //go through all polylines
        //
        //        vector <ofPoint> vertices;
        //        vertices = lines[i].polyline.getVertices(); //get all vertices from this poly
        //
        //        ofSetColor(255);
        //        ofSetLineWidth(1.5);
        //        ofNoFill();
        //
        //        ofBeginShape();
        //        for( int j = 0; j < lines[i].polyline.getVertices().size(); j++) {
        //            ofVertex(lines[i].polyline.getVertices().at(j));
        //        }
        //        ofEndShape();
        //    }
        
        /// -- Draw individual meshes
        //    for(int i=0; i<meshes.size(); i++){
        //        meshes[i].draw();
        //        meshes[i].drawWireframe();
        //    }
        
        /// -- Draw Trapezoids
        ofPushStyle();
        ofSetLineWidth(1);
        
        //--fill
        ofFill();
        for(int i=0; i<lines.size(); i++){
            ofColor boxColor;
            //        for(int j = 0; j<24; j+=6){ //code if we want to change bg of trap on any note hit inside of it
            //            if(lines[i+j].active){
            ////
            ////                if (osc.instOn[i]) colorMod = 255;
            ////                else colorMod = 0;
            ////                cout<<"inston:"<<i<<endl;
            //
            ////                if(colorMod > 250) colorMod = 0;
            //                boxColor.setHsb(80 + 20*i, 255, colorMod, 50);
            //
            //                break;
            //            } else {
            boxColor.setHsb(80 + 20*i, 180, 255, 50);
            //            }
            //        }
            ofSetColor(boxColor);
            
            ofVec2f zonePerp = lines[i].polyline.getVertices().at(1) - lines[i].polyline.getVertices().at(0);
            zonePerp.normalize();
            ofBeginShape();
            if (i<6) {
                drawLines(i, zonePerp);
            }
            ofEndShape();
        }
        
        //-- Outline
        ofNoFill();
        for(int i=0; i<lines.size(); i++){
            
            ofColor boxColor;
            for (int j = 0; j<24; j+=6){
                if(lines[i+j].active){ //look to see if you're in this instrument at all
                    //cout<< "line: "<< i << "is active"<<endl;
                    ofSetLineWidth(2.5);
                    
                    boxColor.setHsb(0, 0, 255);
                    break;
                } else {
                    ofSetLineWidth(1);
                    
                    boxColor.setHsb(50 + 20*i, 180, 255, 200);
                }
            }
            ofSetColor(boxColor);
            
            ofVec2f zonePerp = lines[i].polyline.getVertices().at(1) - lines[i].polyline.getVertices().at(0);
            zonePerp.normalize();
            ofBeginShape();
            if (i<6) {
                drawLines(i, zonePerp);
            }
            ofEndShape();
        }
        
        ofPopStyle(); //-- end instrument trapezoids
        
        /// -- zone highlights, white fading rect on note trigger
        long currTime = ofGetElapsedTimeMillis();
        
        for(int i=0; i<lines.size(); i++){
            ofColor highlightColor;
            for(int j=0; j<26; j+=6){
                if(lines[i+j].active==true){
                    
                    
                    //                if(osc.instOn[0]){ //test an instrument ON
                    //                    ofFill();
                    //                    ofSetColor(255);
                    //                    ofRect(0,0,100,100);
                    //                }
                    
                    if(i < 6){
                        if (osc.instOn[i] && !fading[i+j]){
                            //cout<<osc.instOn[i]<<endl;
                            lines[i+j].activeTimestamp = currTime;
                            fading[i+j] = true;
                        } else  if (!osc.instOn[i]) fading[i+j] = false;
                    }
                    
                    
                    fadeLength[0] = 2;//longest
                    fadeLength[1] = 12.5f;
                    fadeLength[2] = 2;
                    fadeLength[3] = 2;
                    fadeLength[4] = 12.5f;
                    fadeLength[5] = 2; //shortest
                    
                    int whichInstrument;
                    
                    /*this is completely absurd, a travesty and an embarrassment*/
                    if (i==0||i==6||i==12||i==18){
                        whichInstrument = 0;
                    } else if (i==1||i==7||i==13||i==19){
                        whichInstrument = 1;
                    } else if (i==2||i==8||i==14||i==20){
                        whichInstrument = 2;
                    } else if (i==3||i==9||i==15||i==21){
                        whichInstrument = 3;
                    } else if (i==4||i==10||i==16||i==22){
                        whichInstrument = 4;
                    } else if (i==5||i==11||i==17||i==23){
                        whichInstrument = 5;
                    } else if (i==6||i==12||i==18||i==24){
                        whichInstrument = 6;
                    } else cout<<"ERROR"<<endl;
                    
                    
                    long fadeOut = (currTime - (int)lines[i].activeTimestamp)/fadeLength[whichInstrument];
                    if(fadeOut < 100){
                        highlightColor.set(255,255,255, 100 - fadeOut);
                    } else {
                        highlightColor.set(0,0,0,0);
                    }
                    
                    ofSetColor(highlightColor);  //white, opacity over time/2
                    ofFill();
                    
                    ofVec2f zonePerp = lines[i].polyline.getVertices().at(1) - lines[i].polyline.getVertices().at(0);
                    zonePerp.normalize();
                    
                    if(i < 30){
                        ofBeginShape();
                        meshes[i].clear();
                        meshes[i].addColor(highlightColor);
                        meshes[i].addVertex(lines[i].polyline.getCentroid2D());
                        ofVec2f correctedPos = lines[i].polyline.getVertices().at(0) - lines[i].polyline.getVertices().at(1);
                        correctedPos.normalize();
                        
                        for( int j = 0; j < lines[i].polyline.getVertices().size(); j++) {
                            
                            ofVec2f thisVertex;
                            
                            if (j==0) {
                                thisVertex = lines[i].polyline.getVertices().at(j) - correctedPos*(5 - j);
                                meshes[i].addColor(ofColor(255,0));
                                meshes[i].addVertex(thisVertex);
                                ofVertex(thisVertex.x, thisVertex.y);
                                
                            }else if(j==1){
                                thisVertex = lines[i].polyline.getVertices().at(j) + correctedPos*(5 + j);
                                meshes[i].addColor(ofColor(255,0));
                                meshes[i].addVertex(thisVertex);
                                ofVertex(thisVertex.x, thisVertex.y);
                                
                            }else if(j==4){
                                thisVertex = lines[i].polyline.getVertices().at(j) - correctedPos*(5);
                                meshes[i].addColor(ofColor(255,0));
                                meshes[i].addVertex(thisVertex);
                                ofVertex(thisVertex.x, thisVertex.y);
                            }
                            else{
                                thisVertex = lines[i].polyline.getVertices().at(j);
                                meshes[i].addColor(ofColor(255,0));
                                meshes[i].addVertex(thisVertex);
                                ofVertex(thisVertex.x, thisVertex.y);
                            }
                            
                            meshes[i].draw();
                        }
                        
                        ofEndShape();
                    }
                    
                    meshes[i].addColor(ofColor(255,0));
                    
                    
                    
                    
                    
                }
            }
        }
        
        
        /// --  draw circle over blobs for reference
        //    for(int j=0;j<pts.size();j++){
        //        ofSetColor(255,0,0);
        //        ofEllipse(pts[j].x,pts[j].y,10,10);
        //    }
        
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
        
        /// -- Draw Tweets
        tweetText.setText(currentTweet);
        tweetText.setColor(255,255,255,255);
        tweetText.wrapTextX(innerRadius*2-50);
        tweetText.drawCenter(ofGetWidth()/2,ofGetHeight()/2-50);
        
        
        userText.setText(currentUser);
        userText.setColor(200, 255, 150, 255);
        userText.wrapTextX(innerRadius*2-30);
        userText.drawCenter(ofGetWidth()/2,ofGetHeight()/2-80);
        
    }
    
    //--------------------------------------------------------------
    void Bullseye::drawLines(int i, ofVec2f _zonePerp){
        ofVec2f thisVertex;
        ofVec2f scaled;
        
        //    float factor = 10 * sin(ofGetElapsedTimef());
        
        if(osc.beatOn){
            factor = 5;
        }else{
            factor = 0;
        }
        
        factor = 0.05 * (1-factor) * factor; //factor - ofGetElapsedTimeMillis()/1000;
        
        ofVec2f finalPos;
        
        ofVec2f vecToCentroid = lines[i].polyline.getVertices().at(0) - lines[i].polyline.getCentroid2D();
        
        
        thisVertex = lines[i].polyline.getVertices().at(0) + 20*_zonePerp;
        vecToCentroid = lines[i].polyline.getVertices().at(0) - lines[i].polyline.getCentroid2D();
        vecToCentroid.normalize();
        scaled = factor*vecToCentroid;
        finalPos = thisVertex - scaled;
        ofVertex(finalPos.x, finalPos.y);
        
        thisVertex = lines[i].polyline.getVertices().at(1) - 20*_zonePerp;
        vecToCentroid = lines[i].polyline.getVertices().at(1) - lines[i].polyline.getCentroid2D();
        vecToCentroid.normalize();
        scaled = factor*vecToCentroid;
        finalPos = thisVertex - scaled;
        ofVertex(finalPos.x, finalPos.y);
        
        thisVertex = lines[lines.size()-6+i].polyline.getVertices().at(2) - 5*_zonePerp;
        vecToCentroid = lines[lines.size()-6+i].polyline.getVertices().at(2) - lines[lines.size()-6+i].polyline.getCentroid2D();
        vecToCentroid.normalize();
        scaled = factor*vecToCentroid;
        finalPos = thisVertex - scaled;
        ofVertex(finalPos.x, finalPos.y);
        
        thisVertex = lines[lines.size()-6+i].polyline.getVertices().at(3) + 5*_zonePerp ;
        vecToCentroid = lines[lines.size()-6+i].polyline.getVertices().at(3) - lines[lines.size()-6+i].polyline.getCentroid2D();
        vecToCentroid.normalize();
        scaled = factor*vecToCentroid;
        finalPos = thisVertex - scaled;
        ofVertex(finalPos.x, finalPos.y);
        
        thisVertex = lines[i].polyline.getVertices().at(0) + 20*_zonePerp;
        vecToCentroid = lines[i].polyline.getVertices().at(0) - lines[i].polyline.getCentroid2D();
        vecToCentroid.normalize();
        scaled = factor*vecToCentroid;
        finalPos = thisVertex - scaled;
        ofVertex(finalPos.x, finalPos.y);
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