#pragma once

#include "ofMain.h"
#include "text.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        Text newTweets;
};
