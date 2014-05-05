//
//  CameraCV.h
//  Tones
//
//  Created by IncredibleMachines on 2/12/13.
//
//

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ofxXmlSettings.h"
#include "visualPlayer.h"

class CameraCV : public ofBaseApp{
	
public:
    
    void setup();
    void update(bool bAdmin, bool bMouseMode, ofPoint pos1, ofPoint pos2, ofPoint scale1, ofPoint scale2, float rotation1, float rotation2, int cvThreshold, float gain1, float gain2, float gamma1, float gamma2, float shutter1, float shutter2, float brightness1, float brightness2, float contrast1, float contrast2, float hue1, float hue2, vector<visualPlayer> players, int pixelsSample);
    void draw(int show);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    

    ofxXmlSettings XML;
    
    //Camera Tracking
    class blob{
    public:
        ofPoint center;
        bool active;
        bool bNew;
    };
    vector<blob> blobs;
    vector<bool>bNew;
    
    //Mouse Admin Tracking
    vector<ofPolyline>shapes;
    vector<bool>active;
    
    //Camera and Thresholding
    ofPixels pixels, background;
    ofFbo fbo;
    bool bSetBG;
    ofImage saveBG;
    ofxMacamPs3Eye ps3eye;
    ofxMacamPs3Eye ps3eye2;
    int 				camWidth;
    int 				camHeight;
    int imageWidth;
    int imageHeight;
    ofPoint camPos1, camPos2, camScale1, camScale2;
    float rotate1, rotate2;
    int showCV;
    
    
};