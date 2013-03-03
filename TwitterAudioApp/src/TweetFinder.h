#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "ofxOsc.h"
#include "ofxSQLiteHeaders.h"

class Tweet{
        public:
            vector<string> filepaths;
            string message;
            string user;
            int _id;
            int numPlays;
};

class Twitter{
    
    public:
        void setup();
        void update();
    
        vector<string>filepath;
        string returnFilepath();
    
        vector<string>twitterQueries;
    
    
        //*************************************
    
        ofxOscSender player;
        ofxOscReceiver player_callback;
        void sendToPlayer();
        void callback_listener();
    
        //*************************************
    
        int countUnplayedTweets(string _query);
        Tweet getAudioVoices();
        Tweet getTweetFromDB(string _query);
        Tweet getLastPlayedTweet(string _query = "_");

    private:
        ofxSQLite* sqlite;
    
};

