#include "Tones.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 400, 100, OF_WINDOW);
	ofRunApp(new TwitterTones()); // start the app
}
