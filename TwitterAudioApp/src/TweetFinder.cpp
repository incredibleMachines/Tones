#include "TweetFinder.h"

//--------------------------------------------------------------
void Twitter::setup(){
    

    string oscIp = "127.0.0.1";//"10.0.1.44";
    
    player.setup(oscIp, 7002);
    player2.setup(oscIp, 7000);
    player_callback.setup(12345);
    

    sqlite = new ofxSQLite("../../TwitterData/Tweets.db");

    
    //in order of priority
    twitterQueries.push_back("#tones");
    twitterQueries.push_back("#FEEDsxsw");
    twitterQueries.push_back("#sxsw");
    
    
}

void Twitter::update(){
    callback_listener();

    
}

//--------------------------------------------------------------
void Twitter::callback_listener(){

    while (player_callback.hasWaitingMessages()) {
        //ofxOscMessage m;
		//player_callback.getNextMessage(&m);
        cout<<"[CALLBACK_LISTENER] Got Message From Audio" <<endl;
        sendToPlayer();
    }


}

//--------------------------------------------------------------
Tweet Twitter::getAudioVoices(){

    int TotalOptions = 0;
    //check for number of tweets uplayed for each
    Tweet theTweet;
    
    for (int i = 0; i<twitterQueries.size(); i++) {
        if(countUnplayedTweets(twitterQueries[i])>0) {
            
            theTweet = getTweetFromDB(twitterQueries[i]);
            
            for (int i=0; i < theTweet.filepaths.size(); i++) {
                
                cout<< theTweet.filepaths[i] << endl;
            }
            return theTweet;
            //break;
        }else{
            TotalOptions++;
        }
        
        if(TotalOptions == twitterQueries.size()){
        
            //go and get last played priority tweet.
            theTweet = getLastPlayedTweet();
            return theTweet;
        
        }
        
        cout << "Unbroken" <<endl;
    }

}

Tweet Twitter::getLastPlayedTweet(string _query){

    Tweet theTweet;
    string filepath;
    string voice_names;
    
    
    if(_query != "_"){
    
        ofxSQLiteSelect sel = sqlite->select("id,tweet_text,total_plays,user_name,filepath,voice_names")
                                        .from("tweets")
                                        .where("twitter_query", _query)
                                        .order("last_time_played","DESC")
                                        .limit(1);
        
        sel.execute().begin();
        while (sel.hasNext()) {
            int columns = sel.getNumColumns();
            cout << "Number of columns: " << columns<< endl;
            
            for (int i = 0; i<columns; i++) {
                cout << sel.getColumnName(i) << ", ";
            }
            cout << endl;
            
            theTweet._id = sel.getInt();
            theTweet.message = sel.getString();
            theTweet.numPlays=sel.getInt();
            theTweet.user=sel.getString();
            filepath=sel.getString();
            voice_names=sel.getString();
            vector<string> names = ofSplitString(voice_names, ",");
            
            for (int i = 0; i< names.size(); i++) {
                
                string tPath = filepath+"/"+names[i]+".wav";
                theTweet.filepaths.push_back(tPath);
                
            }
            
            
            cout << "id: "<<theTweet._id<< " tweet_text: "<<theTweet.message<<" total_plays: "<<theTweet.numPlays<<
            " user_name: "<<theTweet.user<<" filepath: "<<filepath<<" voice_names: "<<voice_names<<endl;
            
            int total_plays = theTweet.numPlays+1;
            int time =  ofGetUnixTime();
            sqlite->update("tweets").use("last_time_played",time).use("total_plays",total_plays ).where("id", theTweet._id).execute();
            
            sel.next();//break out of the while loop.
        }
        
        
    }else{
    
        ofxSQLiteSelect sel = sqlite->select("id,tweet_text,total_plays,user_name,filepath,voice_names")
                    .from("tweets")
                    .order("last_time_played","DESC")
                    .limit(1);
    
        
        sel.execute().begin();
        while (sel.hasNext()) {
            int columns = sel.getNumColumns();
            cout << "Number of columns: " << columns<< endl;
            
            for (int i = 0; i<columns; i++) {
                cout << sel.getColumnName(i) << ", ";
            }
            cout << endl;
            
            theTweet._id = sel.getInt();
            theTweet.message = sel.getString();
            theTweet.numPlays=sel.getInt();
            theTweet.user=sel.getString();
            filepath=sel.getString();
            voice_names=sel.getString();
            vector<string> names = ofSplitString(voice_names, ",");
            
            for (int i = 0; i< names.size(); i++) {
                
                string tPath = filepath+"/"+names[i]+".wav";
                theTweet.filepaths.push_back(tPath);
                
            }
            
            
            cout << "id: "<<theTweet._id<< " tweet_text: "<<theTweet.message<<" total_plays: "<<theTweet.numPlays<<
            " user_name: "<<theTweet.user<<" filepath: "<<filepath<<" voice_names: "<<voice_names<<endl;
            
            int total_plays = theTweet.numPlays+1;
            int time =  ofGetUnixTime();
            sqlite->update("tweets").use("last_time_played",time).use("total_plays",total_plays ).where("id", theTweet._id).execute();
            
            sel.next();//break out of the while loop.
        }
        
    }
    
    
    return theTweet;
    
}

//--------------------------------------------------------------
Tweet Twitter::getTweetFromDB(string _query){
    

    string filepath;
    string voice_names;
    Tweet theTweet;
    
    ofxSQLiteSelect sel = sqlite->select("id,tweet_text,total_plays,user_name,filepath,voice_names")
                                    .from("tweets")
                                    .whereNull("last_time_played")
                                    .andWhere("twitter_query", _query)
                                    .order("twitter_timestamp","DESC")
                                    .limit(1);
    sel.execute().begin();
    
    while (sel.hasNext()) {
        
        int columns = sel.getNumColumns();
        cout << "Number of columns: " << columns<< endl;
        
        for (int i = 0; i<columns; i++) {
            cout << sel.getColumnName(i) << ", ";
        }
        cout << endl;
        
        theTweet._id = sel.getInt();
        theTweet.message = sel.getString();
        theTweet.numPlays=sel.getInt();
        theTweet.user=sel.getString();
        filepath=sel.getString();
        voice_names=sel.getString();
        vector<string> names = ofSplitString(voice_names, ",");
        
        for (int i = 0; i< names.size(); i++) {
            
            string tPath = filepath+"/"+names[i]+".wav";
            theTweet.filepaths.push_back(tPath);
            
        }
        
        
        cout << "id: "<<theTweet._id<< " tweet_text: "<<theTweet.message<<" total_plays: "<<theTweet.numPlays<<
             " user_name: "<<theTweet.user<<" filepath: "<<filepath<<" voice_names: "<<voice_names<<endl;
        
        int total_plays = theTweet.numPlays+1;
        int time =  ofGetUnixTime();
        sqlite->update("tweets").use("last_time_played",time).use("total_plays",total_plays ).where("id", theTweet._id).execute();
        
        sel.next();//break out of the while loop.
    }

    return theTweet;

}
//--------------------------------------------------------------
int Twitter::countUnplayedTweets(string _query){
    
    ofxSQLiteSelect sel = sqlite->select("count(id) as total").from("tweets").whereNull("last_time_played").andWhere("twitter_query", _query);
    sel.execute().begin();
    int count = sel.getInt();
    cout << "Total Number of " << _query <<" : " << count << endl;
    return count;
}



//--------------------------------------------------------------
void Twitter::sendToPlayer(){
    
    string filepath;
    Tweet thisTweet = getAudioVoices();
    int r = ofRandom(thisTweet.filepaths.size());
    
    filepath=thisTweet.filepaths[r];
    ofStringReplace(filepath,"../../" ,"");
    string fullpath = filepath;
    ofxOscMessage m,n;
    n.setAddress("/file");
    m.setAddress("/tweet");
    m.addStringArg(fullpath);
    m.addStringArg(thisTweet.message);
    m.addStringArg(thisTweet.user);
    n.addStringArg(fullpath);
    player2.sendMessage(n);
    player.sendMessage(m);
    cout << "Sent Message:  " << fullpath << endl;
    

}
//--------------------------------------------------------------
string Twitter::returnFilepath(){

    //string file = filepath[ ofRandom(filepath.size()) -1 ];
    
    string file;
    Tweet thisTweet;
    
    thisTweet = getAudioVoices();
    
    int r = ofRandom(thisTweet.filepaths.size());
    
    file = thisTweet.filepaths[r];
    
    return file;

}
