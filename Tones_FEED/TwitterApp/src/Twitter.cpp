#include "Twitter.h"

//--------------------------------------------------------------
void Twitter::setup(){
    
    bFirstRun = true;
    ofRegisterURLNotification(this);

    populateVoices();
    
    mkdir("../../TwitterData");
    mkdir("../../TwitterData/tweets");

    
//    string days[7] = {"Sun","Mon","Tues", "Wed","Thurs","Fri","Sat"};
//    
//    cout<<"Month: "<< ofGetMonth()<< endl;
//    cout<<"Weekday: "<< days[ofGetWeekday()] <<endl;
//    cout << "Day: " << ofGetDay()<< endl;
//    
//    string sqldb= ofToString(ofGetMonth())+"."+ofToString(ofGetDay())+"_"+days[ofGetWeekday()]+".db";
    sqlite = new ofxSQLite("../../TwitterData/Tweets.db");
    createDatabase();
    
    //string tQueries[] = {"#tones", "#feed","#FEEDsxsw"};
    
    //in order of priority
    twitterQueries.push_back("#TONESsxsw");
    twitterQueries.push_back("#tones");
    twitterQueries.push_back("#FEEDsxsw");
    twitterQueries.push_back("#sxsw");
    
    
}
//--------------------------------------------------------------
void Twitter::populateVoices(){

    //caution this function works to populate available voices from your machine to a vector
    //to test which voices are enabled on your machine uncomment this 

    //printVoices();
    
    //voiceNames.push_back("Agnes");
    //voiceNames.push_back("Albert");
    voiceNames.push_back("Alex");
    //voiceNames.push_back("Bruce");
    //voiceNames.push_back("Fred");
    //voiceNames.push_back("Jill");
    //voiceNames.push_back("Kathy");
    //voiceNames.push_back("Ralph");
    //voiceNames.push_back("Samantha");
    //voiceNames.push_back("Tom");
    voiceNames.push_back("Vicki");
    //voiceNames.push_back("Victoria");
    
    
}
//--------------------------------------------------------------
void Twitter::printVoices(){
    
    /** With time I will add a way to read the result of the iostream and populate this automattically.
    *** for now you must populateVoices() Manually. Sorry.
    **/
    
    //check for all voices
    string availableVoices = "say -v \'?\'";
    
    //print all voices available
    system(availableVoices.c_str());
    
}
//--------------------------------------------------------------
void Twitter::panel(){

}
//--------------------------------------------------------------
void Twitter::update(){
    //cout << ofGetElapsedTimeMillis() << endl;

    if(ofGetElapsedTimeMillis()%300000==0 || bFirstRun){ //make a request every five minutes -- should probably change to whatever the cron runs at.
        ofLoadURLAsync("http://54.235.123.4/installation/retrieve.php");
        bFirstRun = false;
    }
    
    
}


//--------------------------------------------------------------
void Twitter::storeTweet(){


}
//--------------------------------------------------------------
void Twitter::tweetToVoice(ofxJSONElement _json){
    
    string tweet_id = _json["twitter_id"].asString();
    string tweet_text = _json["tweet_text"].asString();
    
    //ofDirectory directory;
    string folder = "../../TwitterData/tweets/"+tweet_id;
    mkdir(folder);
    
    string settings = " --file-format=WAVE --data-format=alaw";
    //if(!directory.doesDirectoryExist(folder)){ //check if dir exists

    //directory.createDirectory(folder);
    //directory.close();
    
    bool bQuiet = false;
    for (int i = 0; i<voiceNames.size(); i++) {
        string filename= tweet_id+"_"+voiceNames[i]+".wav";
        
        string speakText = returnPhraseWithoutURL( tweet_text );
        
        ofStringReplace(speakText, "#", "hashtag ");

        string speak = "say -v "+voiceNames[i]+" -r 160 -o "+filename+settings+" \"" +speakText+ "\" ";
        if(!bQuiet) cout << speak << endl;
        system(speak.c_str());
        
        string move = "mv "+filename+" "+folder;
        if(!bQuiet) cout << move << endl;
        system(move.c_str());
        
        string tFilepath=folder+"/"+filename;
        //storage.push_back(tFilepath);
        if(!bQuiet) cout << "[AUDIO FILEPATH]" << tFilepath << endl;
        //if(i%2==0) sendToPlayer(filepath);

    }


}
//--------------------------------------------------------------
void Twitter::urlResponse(ofHttpResponse &httpResponse){
    if (httpResponse.status==200) {
        
        cout <<httpResponse.data.getText()<< endl;
        
        json.parse(httpResponse.data.getText());
        
        for(int i=0; i<json.size(); i++){
            
            tweetToVoice(json[i]);
            insertTweet(json[i]);
            
            //store the shit in the database... coming soon.
            //tweetToVoice(json[i]["tweet_text"].asString(), json[i]["twitter_id"].asString());
            //tweetToVoice("Sample Text", json[i]["twitter_id"].asString());
        }
        
    }
}
//--------------------------------------------------------------
void Twitter::insertTweet(ofxJSONElement _json){
    
    string folder = "../../TwitterData/tweets/"+ _json["twitter_id"].asString();
    cout<< "inserting tweets" << endl;
    
    string nameString;
    
    for (int i =0; i<voiceNames.size(); i++ ) {
        
        if(i!=0)nameString+=","+voiceNames[i];
        else nameString+=voiceNames[i];
    }
    int voices = voiceNames.size();
    
    string updatedText = returnPhraseWithoutURL(_json["tweet_text"].asString());
    
    sqlite->insert("tweets")
    .use("twitter_id",_json["twitter_id"].asString())
    .use("twitter_timestamp", _json["twitter_timestamp"].asInt())
    .use("twitter_query", _json["twitter_query"].asString())
    .use("tweet_text",updatedText)
    //    .use("last_time_played",03223)
    .use("total_plays",0)
    .use("user_name",_json["user_name"].asString())
    .use("filepath",folder)
    .use("num_voices", voices)
    .use("voice_names",nameString)
	.execute();
    
}


//--------------------------------------------------------------
void Twitter::createDatabase(){
    
    if (SQLITE_OK != sqlite->simpleQuery(""\
                        "CREATE TABLE IF NOT EXISTS tweets"\
                        "(id INTEGER PRIMARY KEY  AUTOINCREMENT,"\
                            "twitter_id TEXT,"\
                            "twitter_timestamp INTEGER,"\
                            "twitter_query TEXT,"\
                            "tweet_text TEXT,"\
                            "last_time_played INTEGER,"\
                            "total_plays INTEGER,"\
                            "user_name TEXT,"\
                            "filepath TEXT,"\
                            "num_voices INTEGER,"\
                            "voice_names TEXT"\
                        ");"
        )){cout << "[SQLITE DATABASE ERROR] CREATE TABLE ISSUE\n";
	}

}

string Twitter::returnPhraseWithoutURL(string _phrase){
    
    vector<string> words = ofSplitString(_phrase, " ");
    string newPhrase;
    string  s= "http://";
    
    for (int i = 0; i< words.size(); i++) {
        
        int loc =  words[i].find(s);
        
        if(loc != -1) words[i] = "";
        
    }
    
    for (int i = 0; i< words.size(); i++) newPhrase += words[i]+" ";
    
    return newPhrase;
    
    
}


//--------------------------------------------------------------
int Twitter::mkdir(string path){
    string s = "mkdir "+path;
    int i = system(s.c_str());
    return i;
}