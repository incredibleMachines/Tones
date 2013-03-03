//
//  CameraCV.cpp
//  Tones
//
//  Created by IncredibleMachines on 2/12/13.
//
//

#include "CameraCV.h"

//--------------------------------------------------------------
void CameraCV::setup(){
        //test
    ofFbo::Settings s=ofFbo::Settings();
    s.width=ofGetWidth();
    s.height=ofGetHeight();
    s.useDepth=false;
    s.internalformat=GL_RGB;
    s.useStencil=false;
    s.numSamples=0;
    
    fbo.allocate(s);
	
	camWidth = 640;
	camHeight = 480;
	
	ps3eye.listDevices();
    ps3eye.setDeviceID(2);
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight,false);
    
    ps3eye2.listDevices();
    ps3eye2.setDeviceID(3);
	ps3eye2.setDesiredFrameRate(60);
	ps3eye2.initGrabber(camWidth,camHeight,false);
	
    //CAMERA 1 SETTINGS
	ps3eye.setAutoGainAndShutter(false);
	
    //CAMERA 2 SETTINGS
	ps3eye2.setAutoGainAndShutter(false);
    
    //DEFAULT VIEW OF NOT DRAWING CAMERA
    showCV=false;
    
    bSetBG=false;
    saveBG.loadImage("background.jpg");
    background.setFromPixels(saveBG.getPixels(),saveBG.getWidth(),saveBG.getHeight(),OF_IMAGE_COLOR);
    
    for (int i=0; i<6;i++){
        blob temp;
        blobs.push_back(temp);
        ofPolyline shape;
        shapes.push_back(shape);
        active.push_back(false);
        bNew.push_back(false);
    }
    
}


//--------------------------------------------------------------
void CameraCV::update(bool bAdmin, bool bMouseMode, ofPoint pos1, ofPoint pos2, ofPoint scale1, ofPoint scale2, float rotation1, float rotation2, int threshold, float gain1, float gain2, float gamma1, float gamma2, float shutter1, float shutter2, float brightness1, float brightness2, float contrast1, float contrast2, float hue1, float hue2, vector<visualPlayer> players, int pixelSample){
    
    blobs.clear();
    if(bAdmin){
        ps3eye.setGain(gain1);
        ps3eye.setShutter(shutter1);
        ps3eye.setGamma(gamma1);
        ps3eye.setBrightness(brightness1);
        ps3eye.setContrast(contrast1);
        ps3eye.setHue(hue1);
        ps3eye.setFlicker(0);
        
        ps3eye2.setGain(gain2);
        ps3eye2.setShutter(shutter2);
        ps3eye2.setGamma(gamma2);
        ps3eye2.setBrightness(brightness2);
        ps3eye2.setContrast(contrast2);
        ps3eye2.setHue(hue2);
        ps3eye2.setFlicker(0);
        
        //GET GLOBALS FROM ADMIN GUI
        camPos1.x=pos1.x;
        camPos1.y=pos1.y;
        camScale1.x=scale1.x;
        camScale1.x=camScale1.x/100;
        camScale1.y=scale1.y;
        camScale1.y=camScale1.y/100;
        rotate1=rotation1;
        
        camPos2.x=pos2.x;
        camPos2.y=pos2.y;
        camScale2.x=scale2.x;
        camScale2.x=camScale2.x/100;
        camScale2.y=scale2.y;
        camScale2.y=camScale2.y/100;
        rotate2=rotation2;
        
    }
    
    if (bMouseMode==true){
        for(int i=0;i<players.size();i++){
            ofVec2f widthAngle=players[i].baseLine.getPerpendicular();
            ofVec2f masterWidth=widthAngle;
            masterWidth.scale(players[i].viewerWidth/2);
            ofVec2f viewerOrigin=players[i].viewerOrigin;
            ofVec2f viewerDraw=viewerOrigin+masterWidth;
            ofVec2f viewerBaseLine=players[i].handle-viewerOrigin;
            shapes[i].clear();
            shapes[i].addVertex(viewerDraw);
            shapes[i].addVertex(players[i].viewerOrigin-masterWidth);
            shapes[i].addVertex(players[i].viewerOrigin-masterWidth+viewerBaseLine);
            shapes[i].addVertex(viewerDraw+viewerBaseLine);
            shapes[i].close();
        }
    }
    
	ps3eye.update();
    ps3eye2.update();
    
	if((ps3eye.isFrameNew()&&ps3eye2.isFrameNew())){
        fbo.begin();
        ofBackgroundHex(0x000000);
        ofSetHexColor(0xffffff);
        ofPushMatrix();
        ofScale(camScale1.x,camScale1.y);
        ofTranslate(camPos1.x,camPos1.y);
        ofPushMatrix();
        ofTranslate(camWidth/2,camHeight/2);
        ofRotate(rotate1);
        ps3eye.draw(-(camWidth/2),-(camHeight/2),camWidth,camHeight);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofScale(camScale2.x,camScale2.y);
        ofTranslate(camPos2.x,camPos2.y);
        ofPushMatrix();
        ofTranslate(camWidth/2,camHeight/2);
        ofRotate(rotate2);
        ps3eye2.draw(-(camWidth/2), -(camHeight/2),camWidth, camHeight);
        ofPopMatrix();
        ofPopMatrix();
        fbo.end();
        
        //get FBO pixels
        fbo.readToPixels(pixels);
        
        if(bSetBG==true){
            background=pixels;
            saveBG.allocate(pixels.getWidth(),pixels.getHeight(),OF_IMAGE_COLOR);
            saveBG.setFromPixels(pixels);
            saveBG.saveImage("background.jpg",OF_IMAGE_QUALITY_BEST);
            saveBG.update();
            bSetBG=false;
        }
        
        for(int i=0; i<players.size();i++){
            ofVec2f widthAngle=players[i].baseLine.getPerpendicular();
            ofVec2f masterWidth=widthAngle;
            masterWidth.scale(players[i].viewerWidth/2);
            ofVec2f viewerOrigin=players[i].viewerOrigin;
            ofVec2f viewerDraw=viewerOrigin+masterWidth;
            ofVec2f viewerBaseLine=players[i].handle-viewerOrigin;

            int pixelCount=0;
            vector<ofVec2f> centerPix;
            for(int k=viewerBaseLine.length();k>0;k--){
                if(pixelCount>pixelSample){
                    break;
                }
                ofVec2f currentVec;
                currentVec=viewerBaseLine;
                currentVec.scale(k);
                for(int j=0;j<players[i].viewerWidth;j++){
                    if(pixelCount>pixelSample){
                        break;
                    }
                    ofVec2f xVec;
                    xVec=masterWidth;
                    xVec.scale(j);
                    ofVec2f current=currentVec-xVec;
                    current=current + viewerDraw;
                    if(current.x<ofGetWidth()&&current.x>0&&current.y<ofGetHeight()&&current.y<ofGetWidth()){
                        if(abs(pixels[3*int(current.x)+int(current.y)*(3*pixels.getWidth())]-background[3*int(current.x)+int(current.y)*(3*pixels.getWidth())])>threshold){
                            centerPix.push_back(current);
                        }
                    }
            }
            }
            
            if (centerPix.size()>0){
                if(blobs[i].active==false){
                    bNew[i]=true;
                }
                ofVec2f centerPixTotal;
                for(int j=0;j<centerPix.size();j++){
                    centerPixTotal.x+=centerPix[j].x;
                    centerPixTotal.y+=centerPix[j].y;
                }
                blobs[i].center.x=centerPixTotal.x/centerPix.size();
                blobs[i].center.y=centerPixTotal.y/centerPix.size();
                blobs[i].active=true;
            }
            else {
                bNew[i]=false;
                blobs[i].active=false;
            }
            centerPix.clear();
        }
    }
}

//--------------------------------------------------------------
void CameraCV::draw(int show){
    showCV=show;
    
    if(showCV==1){

        saveBG.draw(0,0);
    }
    
    
    if(showCV==2){
        fbo.draw(0,0);
    }
}



//--------------------------------------------------------------
void CameraCV::keyPressed  (int key){
    if(showCV!=0){
        if(key == ' ') {
            bSetBG=true;
        }
    }
}

//--------------------------------------------------------------
void CameraCV::keyReleased(int key){
	
}

//--------------------------------------------------------------
void CameraCV::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void CameraCV::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void CameraCV::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void CameraCV::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void CameraCV::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void CameraCV::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void CameraCV::dragEvent(ofDragInfo dragInfo){
    
}