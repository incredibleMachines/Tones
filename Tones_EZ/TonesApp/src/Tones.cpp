#include "Tones.h"



//--------------------------------------------------------------
void Tones::setup(){
    //oFSettings
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetWindowShape(800,800);
    
    //camera + stage alignment USER SETTABLE
    camZoom.x=0;
    camZoom.y=0;
    camOffset.x=0;
    camOffset.y=0;
    
    //Camera Settings
    camWidth = 320;//640;
    camHeight = 240;//480;
    camera.setup(camWidth, camHeight);  //-- ofxPs3Eye
    admin.setup();
    XML.loadFile("xml/settings.xml");
    camera.ps3eye.setBrightness(admin.gui.getValueF("CAM1:BRIGHTNESS"));
    camera.ps3eye.setGamma(admin.gui.getValueF("CAM1:GAMMA"));
    camera.ps3eye.setContrast(admin.gui.getValueF("CAM1:CONTRAST"));
    camera.ps3eye.setHue(admin.gui.getValueF("CAM1:HUE"));
    threshold = admin.gui.getValueF("CAM1:THRESH");
    
    //Stage Alignment Variables
    stageCenterX = ofGetWidth()/2;
    stageCenterY = ofGetHeight()/2;
    stagingX = camOffset.x; 
    stagingY = camOffset.y;
    stageWidth = ofGetWidth()+camZoom.x;
    stageHeight = ofGetHeight()+camZoom.y;
    
    //CV image variables
    colorImg.allocate(camWidth,camHeight);
	grayImage.allocate(camWidth,camHeight);
	grayBg.allocate(camWidth,camHeight);
	grayDiff.allocate(camWidth,camHeight);
	bLearnBakground = false;
    blobDist = 100; //distance in pixels under which blobs will be combined/ignored **USER SETTABLE**
    
    //Output Settings
    stageState = 2; //0=camera raw; 1=CV debug; 2=Live **USER SETTABLE**
    tex.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    
    // Setup functions                      //-- admin gui
    stage.setup();                      //-- bullseye stage
    loadLatestBgCapture(); //pull last captured BG image from file!
    
    //*** MOUSE AS BLOB SOURCE, DISABLES CAMERA BLOBS FROM TRIGGERING NOTES ***//
    mouseAsBlob = true; //for debug purposes
    nMouseBlobs = 1; //supports up to 4 only!
}

//--------------------------------------------------------------
void Tones::update(){
    
    if (camera.update()){ //returns true if frame is new
        colorImg.setFromPixels(camera.getPixels(), camWidth, camHeight);
        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            /*** save this new bg image to file! ***/
            ofImage backgroundImg;
            backgroundImg.setFromPixels(camera.getPixels(), camWidth, camHeight, OF_IMAGE_COLOR);
            string archiveFileName = "bg_background_capture_"+ofGetTimestampString()+".png"; //dated
            string fileName = "bg_latestBackgroundCapture.png"; //static name
            backgroundImg.saveImage(fileName);
            backgroundImg.saveImage(archiveFileName);
            cout<<"SAVED BG IMAGE: "<< archiveFileName << endl;
            
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiff, 20, (camWidth*camHeight)/3, 10, true);	// find holes
    }
    
    blobs.clear();
    pts.clear();
    
    for (int i = 0; i < contourFinder.nBlobs; i++){ //for every blob
        float distFromCenter = ofDist(contourFinder.blobs[i].centroid.x,
                                      contourFinder.blobs[i].centroid.y, camWidth/2, camHeight/2);
        ofPoint blobClosest;
        
        
        //        contourFinder.blobs[i].draw( stagingX, stagingY ); //draw this blob on the stage
        
        bool bNewBlob=true;
        
        for(int j=0; j<blobs.size();j++){
            if (ofDist(contourFinder.blobs[i].centroid.x,
                       contourFinder.blobs[i].centroid.y, blobs[j].blob.centroid.x, blobs[j].blob.centroid.y)<blobDist)
            {
                bNewBlob=false;
                if(distFromCenter<blobs[j].centroidDist){
                    blobs[j].blob=contourFinder.blobs[i];
                    blobs[j].centroidDist=distFromCenter;
                    float blobCenterDist;
                    for(int k=0;k<blobs[j].blob.nPts;k++){
                        if(k==0){
                            blobCenterDist=ofDist(blobs[j].blob.pts[k].x+stagingX,
                                                  blobs[j].blob.pts[k].y+stagingY, stageCenterX, stageCenterY);
                            blobClosest.x=blobs[j].blob.pts[k].x+stagingX;
                            blobClosest.y=blobs[j].blob.pts[k].y+stagingY;
                        }
                        float currentCenterDist=ofDist(blobs[j].blob.pts[k].x+stagingX,
                                                       blobs[j].blob.pts[k].y+stagingY, stageCenterX, stageCenterY);
                        if(currentCenterDist<blobCenterDist){
                            blobCenterDist=currentCenterDist;
                            blobClosest.x=blobs[j].blob.pts[k].x+stagingX;
                            blobClosest.y=blobs[j].blob.pts[k].y+stagingY;
                        }
                    }
                    blobs[j].closest=blobClosest;
                }
            }
        }
        
        if(bNewBlob==true){
            Blob tempBlob;
            tempBlob.blob=contourFinder.blobs[i];
            tempBlob.centroidDist=distFromCenter;
            float blobCenterDist;
            for(int k=0;k<tempBlob.blob.nPts;k++){
                if(k==0){
                    blobCenterDist=ofDist(tempBlob.blob.pts[k].x,
                                          tempBlob.blob.pts[k].y,camWidth/2, camHeight/2);
                    blobClosest.x=tempBlob.blob.pts[k].x+stagingX;
                    blobClosest.y=tempBlob.blob.pts[k].y+stagingY;
                }
                float currentCenterDist=ofDist(tempBlob.blob.pts[k].x,
                                               tempBlob.blob.pts[k].y,camWidth/2, camHeight/2);
                if(currentCenterDist<blobCenterDist){
                    blobCenterDist=currentCenterDist;
                    blobClosest.x=tempBlob.blob.pts[k].x;
                    blobClosest.y=tempBlob.blob.pts[k].y;
                    
                }
            }
            tempBlob.closest=blobClosest;
            blobs.push_back(tempBlob);
        }

    }
    if(mouseAsBlob){
        pts.clear();
        for (int i=0; i<nMouseBlobs; i++){
            ofPoint mouse;
            if(i == 0){
                mouse.x = mouseX;
                mouse.y = mouseY;
            } else if (i==1){
                mouse.x = ofGetWidth() - mouseX;
                mouse.y = ofGetHeight() - mouseY;
            } else if (i==2){
                mouse.x = ofGetWidth() - mouseX;
                mouse.y = mouseY;
            } else if(i ==3){
                mouse.x = mouseX;
                mouse.y = ofGetHeight() - mouseY;
            } else break;
            pts.push_back(mouse);
        }
    }
    
    else{
        for(int j=0; j<blobs.size();j++){
            ofVec2f thisBlob;
            thisBlob.x=ofMap(blobs[j].closest.x,0,camWidth,0,stageWidth);
            thisBlob.x+=stagingX;
            thisBlob.y=ofMap(blobs[j].closest.y,0,camHeight,0,stageHeight);
            thisBlob.y+=stagingY;
            pts.push_back(thisBlob);
        }
    }
    
    stage.update();
    
    if(bDrawAdmin) {
     admin.update();
        camera.ps3eye.setBrightness(admin.gui.getValueF("CAM1:BRIGHTNESS"));
        
        //    gain1=gui.getValueF("CAM1:GAIN:CURRENT");
        camera.ps3eye.setGamma(admin.gui.getValueF("CAM1:GAMMA"));
        //    shutter1=gui.getValueF("CAM1:SHUTTER:CURRENT");
        camera.ps3eye.setContrast(admin.gui.getValueF("CAM1:CONTRAST"));
        camera.ps3eye.setHue(admin.gui.getValueF("CAM1:HUE"));
        threshold=admin.gui.getValueF("CAM1:THRESH");
    }
}

//--------------------------------------------------------------
void Tones::draw(){
    
    ofBackground(10,10,10);
    //------------------------- debug camera view -- raw camera input
    if (stageState == 0){ 
        camera.draw(stagingX, stagingY, stageWidth, stageHeight);
        for(int j=0;j<pts.size();j++){
             ofFill();
            ofSetColor(255,0,0);
            ofEllipse(pts[j].x,pts[j].y,10,10);
        }
    }
    //------------------------- debug image processing
    else if(stageState == 1){
        // draw the incoming, the grayscale, the bg and the thresholded difference
        ofSetHexColor(0xffffff);
        colorImg.draw(20,20);
        grayImage.draw(360,20);
        grayBg.draw(20,280);
        grayDiff.draw(360,280);
        
        
        // then draw the contours:
        ofFill();
        ofSetHexColor(0x333333);
        ofRect(360,540,320,240);
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        //contourFinder.draw(360,540);
        
        // or, instead we can draw each blob individually from the blobs vector,
        // this is how to get access to them:
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(360,540);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            if(contourFinder.blobs[i].hole){
                ofDrawBitmapString("hole",
                                   contourFinder.blobs[i].boundingRect.getCenter().x + 360,
                                   contourFinder.blobs[i].boundingRect.getCenter().y + 540);
            }
        }
        
        // finally, a report:
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press 'b' to capture bg" << endl
        << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 600);
    }
    
    //------------------------- play time (much will move to it's own class)
    else if(stageState == 2){

        
//        camera.draw(stagingX, stagingY, ofGetWidth(), ofGetHeight());
         
        // then draw the contours:
        ofFill();
        ofSetColor(100, 100, 100, 100);
        ofRect(stagingX, stagingY, stageWidth, stageHeight);

        stage.draw();
    }
    ofSetColor(0);
    ofDrawBitmapString(ofToString(mouseX)+" "+ofToString(mouseY), mouseX, mouseY);
    
    ///SYPHON
    tex.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    individualTextureSyphonServer.publishTexture(&tex);
    ofSetColor(255);
    
        if(bDrawAdmin) admin.draw();
    }

//--------------------------------------------------------------
void Tones::keyPressed(int key){
	switch (key){
		case 'b':
            //camera.saveBackgroundCaptureImg();
            //loadLatestBgCapture();
			bLearnBakground = true;
			break;
            
        case ' ':
            stageState++;
            if (stageState>2) stageState = 0;
            cout<<"stageState: "<<stageState<<endl;
            break;
            
        case 'c':
            camera.printCurrentSettings();
            break;
        
        case '`':
            bDrawAdmin = !bDrawAdmin;
            cout<<"bDrawAdmin = "<<bDrawAdmin<<endl;
            break;
        
        case 'm':
            mouseAsBlob = !mouseAsBlob; //use mouse as a blob
            break;
            
        case 't':
            stage.toggleTranslucentMode();
            break;

	}
    
    if(bDrawAdmin){
        admin.keyPressed(key);
    }
}

//--------------------------------------------------------------
void Tones::keyReleased(int key){
    if(bDrawAdmin){
        admin.keyReleased(key);
    }

}

//--------------------------------------------------------------
void Tones::mouseMoved(int x, int y){
    if(bDrawAdmin){
        admin.mouseMoved(x,y);
    }

}

//--------------------------------------------------------------
void Tones::mouseDragged(int x, int y, int button){
    if(bDrawAdmin){
        admin.mouseDragged(x,y,button);
    }
    
}

//--------------------------------------------------------------
void Tones::mousePressed(int x, int y, int button){
    if(bDrawAdmin){
        admin.mousePressed(x,y,button);
    }


}

//--------------------------------------------------------------
void Tones::mouseReleased(int x, int y, int button){
    if(bDrawAdmin){
        admin.mouseReleased(x,y,button);
    }
    
}

//--------------------------------------------------------------
void Tones::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void Tones::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void Tones::dragEvent(ofDragInfo dragInfo){
    
}

void Tones::loadLatestBgCapture(){
    
    capturedBgImage.loadImage("bg_latestBackgroundCapture.png"); //load latest
    ofxCvColorImage tmpBg;
    tmpBg.setFromPixels(capturedBgImage.getPixels(), 320, 240);  //set into cvColorImage
    grayImage.setFromColorImage(tmpBg);                          //set grayImage to our bg
    grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
    
    colorImgStage=colorImg;
    colorImgStage.resize(stageWidth, stageHeight);
    grayImageStage.resize(colorImgStage.width, colorImgStage.height);
    grayImageStage = colorImgStage;
    grayBgStage.resize(grayImageStage.width, grayImageStage.height);
    grayBgStage = grayImageStage;
    
    bLearnBakground = false;
}


//--------------------------------------------------------------
void Player::setPlayer(int _index, int _note, int _inst){
    index = _index;
    note = _note;
    instrument = _inst;
}
