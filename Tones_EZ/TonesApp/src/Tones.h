#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ofxControlPanel.h"
#include "ofxOpenCv.h"
#include "AdminWindow.h"
#include "ofxSyphon.h"
#include "Camera.h"
#include "Bullseye.h"


class Player {
public:
    int index;
    int note;
    int instrument;
    
    void setPlayer(int _index, int _note, int _inst);
    
};

class Blob {
public:
    ofxCvBlob blob;
    ofPoint closest;
    int centroidDist;
};

class Tones : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void testMouse(int pullAmount, int speed);
    
    void loadLatestBgCapture();
    
    Camera camera;
    
    int camWidth;
    int camHeight;
    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvContourFinder      contourFinder;

    
    int stageWidth;
    int stageHeight;
    ofPoint camZoom, camOffset;
    ofxCvColorImage			colorImgStage;
    ofxCvGrayscaleImage 	grayImageStage;
    ofxCvGrayscaleImage 	grayBgStage;
    ofxCvGrayscaleImage 	grayDiffStage;
    ofxCvContourFinder      contourFinderStage;
    ofImage capturedBgImage;
    
    int 				threshold;
    bool				bLearnBakground;
    
    bool                bDrawAdmin;
    int                 stageState;
    
    ofxXmlSettings XML;
    AdminWindow admin;
    
    vector<ofPoint> pts;
    vector<Blob> blobs;
    int blobDist;
    
    vector<Player> players;
    
    int stageCenterX, stageCenterY, stagingX, stagingY, offset;
    
    //-- debug
    bool mouseAsBlob;
    int nMouseBlobs;

    //--- bullseye stage animation
    Bullseye stage;
    
    //--- syphon
    ofTexture tex;
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
    
    //--GUI
    bool bShowGui;
    
};
