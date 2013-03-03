#include "ofMain.h"
#include "Tones.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    window.setGlutDisplayString("rgba double samples>=2");
	ofSetupOpenGL(&window, 1200, 960, OF_WINDOW);
	ofRunApp(new Tones()); // start the app
}
