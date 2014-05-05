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
        void panel();
    
        void urlResponse(ofHttpResponse &httpResponse);

        void storeTweet();
        void tweetToVoice(ofxJSONElement _json);
    
        void populateVoices();
        void printVoices();
    
        //*************************************
    
        ofxJSONElement json;
        bool parsed;
        vector <string> voiceNames;
        string baseScript;
        string tweetText;
        int mkdir(string path);
        bool bFirstRun;
    
        vector<string>filepath;
        string returnFilepath();
    
        vector<string>twitterQueries;
    
        string returnPhraseWithoutURL(string _phrase);
    
    
        //*************************************
//    
//        ofxOscSender player;
//        ofxOscReceiver player_callback;
//        void sendToPlayer();
//        void callback_listener();
    
        //*************************************
    
//        int countUnplayedTweets(string _query);
//        Tweet getAudioVoices();
//        Tweet getTweetFromDB(string _query);
//        Tweet getLastPlayedTweet(string _query = "_");

    private:
        ofxSQLite* sqlite;
        void createDatabase();
        void insertTweet(ofxJSONElement _json);
        
    

};

