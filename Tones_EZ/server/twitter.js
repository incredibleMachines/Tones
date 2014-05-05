/* MONGO DB SETUP 
-------------------
*/
var MongoClient = require('mongodb').MongoClient,
	Server = require('mongodb').Server,
	mongo = new MongoClient(new Server('localhost', 27017)),
	BSON = require('mongodb').BSONPure;
	
var dbTones, colTweets;
	
mongo.open(function(err,mongo){
	if(err)console.error(err);
	console.log("Database Connected");
	dbTones = mongo.db('tones');
	colTweets = dbTones.collection('tweets');

});
/* ------------------- */

/* COLORED OUTPUT SETUP 
------------------------
*/
var colors = require('colors');
colors.setTheme({
  info: 'green',
  data: 'grey',
  help: 'cyan',
  warn: 'yellow',
  debug: 'blue',
  error: 'red'
});

/* ------------------- */

/* TWITTER & AUDIO SETUP 
------------------------
*/

var ImmortalNTwitter = require('immortal-ntwitter');

var sys = require('sys');
var exec = require('child_process').exec;

var S = require('string');


// Profanity list

var profanity = [
'2g1c','2 girls 1 cup','acrotomophilia','anal','anilingus','anus','arsehole','ass','asshole','assmunch','auto erotic','autoerotic','babeland','baby batter','ball gag','ball gravy','ball kicking','ball licking','ball sack','ball sucking','bangbros','bareback','barely legal','barenaked','bastardo','bastinado','bbw','bdsm','beaver cleaver','beaver lips','bestiality','bi curious','big black','big breasts','big knockers','big tits','bimbos','birdlock','bitch','black cock','blonde action','blonde on blonde action','blow j','blow job','blow your l', 'blow your load','blue waffle','blumpkin','bollocks','bondage','boner','boob','boobs','booty call','brown showers','brunette action','bukkake','bulldyke','bullet vibe','bung hole','bunghole','busty','butt','buttcheeks','butthole','camel toe','camgirl','camslut','camwhore','carpet muncher','carpetmuncher','chocolate rosebuds','circlejerk','cleveland steamer','clit','clitoris','clover clamps','clusterfuck','cock','cocks','coprolagnia','coprophilia','cornhole','cum','cumming','cunnilingus','cunt','darkie','date rape','daterape','deep throat','deepthroat','dick','dildo','dirty pillows','dirty sanchez','dog style','doggie style','doggiestyle','doggy style','doggystyle','dolcett','domination','dominatrix','dommes','donkey punch','double dong','double penetration','dp action','eat my ass','ecchi','ejaculation','erotic','erotism','escort','ethical slut','eunuch','faggot','fecal','felch','fellatio','feltch','female squirting','femdom','figging','fingering','fisting','foot fetish','footjob','frotting','fuck', '#fuck','fucking', 'fuck1ng', 'fuckin', 'fucka','fuck buttons','fudge packer','fudgepacker','futanari','g-spot','gang bang','gay sex','genitals','giant cock','girl on','girl on top','girls gone wild','goatcx','goatse','gokkun','golden shower','goo girl','goodpoop','goregasm','grope','group sex','guro','hand job','handjob','hard core','hardcore','hentai','homoerotic','honkey','hooker','hot chick','how to kill','how to murder','huge fat','humping','incest','intercourse','jack off','jail bait','jailbait','jerk off','jigaboo','jiggaboo','jiggerboo','jizz','juggs','kike','kinbaku','kinkster','kinky','knobbing','leather restraint','leather straight jacket','lemon party','lolita','lovemaking','make me come','male squirting','masturbate','menage a trois','milf','missionary position','motherfucker','mound of venus','mr hands','muff diver','muffdiving','nambla','nawashi','negro','neonazi','nig nog','nigga','nigger','nimphomania','nipple','nipples','nsfw images','nude','nudity','nympho','nymphomania','octopussy','omorashi','one cup two girls','one guy one jar','orgasm','orgy','paedophile','panties','panty','pedobear','pedophile','pegging','penis','phone sex','piece of shit','piss pig','pissing','pisspig','playboy','pleasure chest','pole smoker','ponyplay','poof','poop chute','poopchute','porn','porno','pornography','prince albert piercing','pthc','pubes','pussy','queaf','raghead','raging boner','rape','raping','rapist','rectum','reverse cowgirl','rimjob','rimming','rosy palm','rosy palm and her 5 sisters','rusty trombone','s&m','sadism','scat','schlong','scissoring','semen','sex','sexo','sexy','shaved beaver','shaved pussy','shemale','shibari','shit','shota','shrimping','slanteye','slut','smut','snatch','snowballing','sodomize','sodomy','spic','spooge','spread legs','strap on','strapon','strappado','strip club','style doggy','suck','sucks','suicide girls','sultry women','swastika','swinger','tainted love','taste my','tea bagging','threesome','throating','tied up','tight white','tit','tits','titties','titty','tongue in a','topless','tosser','towelhead','tranny','tribadism','tub girl','tubgirl','tushy','twat','twink','twinkie','two girls one cup','undressing','upskirt','urethra play','urophilia','vagina','venus mound','vibrator','violet blue','violet wand','vorarephilia','voyeur','vulva','wank','wet dream','wetback','white power','women rapping','wrapping men','wrinkled starfish','xx','xxx','yaoi','yellow showers','yiffy','zoophilia','motherfucker','mothafucka','fuck','fuch'
];


//twitter creds for three different accounts select the appropriate account, 
//make sure you're not using the same one as another application

var EZ1 = {
	consumer_key: 'qoRqHl8ZRufiIYxi5ed1w', 
	consumer_secret: 'Wfbp8NFs8HgFeAWe925GJaS6qcvFdIpEswXOa1VZNQ',
	access_token_key: '1534210819-GrFRLYMqMmRi1RtAjRFMUOwijGQUUAf9paDmq8l',
	access_token_secret: 'i3xmmUx21VjV61yZB84vvNvjdQjHIfMNwpwF9HBNXnM'
	
};

var EZ2 = {
	consumer_key: 'Zr9dtpvnSjQ7ulYwkg9ecA',
	consumer_secret: '2j5wleaf8fUFGIiFgsYJI2pFTHrpa0UvKttWIfQLidk',
	access_token_key: '1534210819-8bLdKgPWkaaxAfVkBHhEVuKiRIq7f7KlWfp4xJp',
	access_token_secret:'xRAhhRZOX4T37KwXshhKzXhZsVZ6lqcJ1S7PpDH5w'
	
};

var DEV = {
      consumer_key:         'kSYh8Wp9YnNsVo9Qc85mSw',
      consumer_secret:      'mOgzzfUNyaRctQyUxQtP68qXJmPcI80XG8jmsnigEE',
      access_token_key:     '1534210819-dNFSOjjhEY2DQuZ4bcRIMbT0SMJnbaKsPjmveyS',
      access_token_secret:  'y0b4p8CLWOSYUVcdQn2O9fpNSDRi10KdyTlIysbv6uo'
    };

var twitter = ImmortalNTwitter.create(DEV);




var trackPhrases = ['riot fest', 'riotfest', '#makeitMEGA' ];

//the string we need to track tweets with
var trackString = trackPhrases.join();

var following = ['1716295890', 
				 '19726058']; //@makeitMEGA && @riotfest user_ids

var followingString = following.join();

/* ------------------- */

/* OSC SETUP 
------------------------
*/
var osc = require('node-osc');

var oscClient1 = new osc.Client('127.0.0.1', 7002);
var oscClient2 = new osc.Client('127.0.0.1', 7000);
var oscServer = new osc.Server(12345, '0.0.0.0');

/* RUN TWITTER STREAM FOR RESULTS */
twitter.immortalStream('statuses/filter', { track: trackString, follow: followingString, stall_warnings: true }, function(stream){
	
		// Process with our callback
		stream.on('data', function(data){
		
			processIncomingTweet(data);
			console.log("[TWEET TEXT] ".help+data.text.data);
			console.log("[TWEET ID] ".help+data.id_str.data);
			
		});

		//Deal with errors
		stream.on('error', function(error, code){
			console.error('[TWITTER] Error! Code: ' + code);
			console.error(error);
			//throw error;
		});
		stream.on('end', function (response) {
			// Handle a disconnection
			console.log('[TWITTER] End:');
			console.log(response);
		});
		stream.on('destroy', function (response) {
			// Handle a 'silent' disconnection from Twitter, no end/error event fired
			console.log('[TWITTER] Destroy:');
			console.log(response);
		});
	
});


oscServer.on("message",function(msg, rinfo){
	console.log("---------------------INCOMING OSC---------------");
	
	//query DB for last unplayed TWEET
	//OSC back filepath, user and text information
	//update DB play-count
	
	getAudioFile(function(tweet_obj){
		//console.log(tweet_obj);
		//console.log('Prepping OSC');

		var msg1 = new osc.Message("/tweet", tweet_obj.incoming_text, tweet_obj.user);
		var msg2 = new osc.Message("/file", tweet_obj.audio_file); 
		
		
		oscClient1.send(msg1);
		oscClient2.send(msg2);
		
		//console.log('Sent OSC');
		//update object
		
		var obj = { _id : new BSON.ObjectID( String(tweet_obj._id) ) };
		var json = {$set:{ last_played: new Date() }, $inc: {play_count: 1}};
		colTweets.update(obj, json,function(err){
			if(err) console.error(err); //throw err;
		});
		
				
	});

});

/* GET FILE, TWEET TEXT & USER TO APP & AUDIO PLAYER */


var getAudioFile= function(callback){
	
	//find object where playcount = 0 
	//sort by timestamp
	
	var obj = {play_count: 0};
	var sort = {timestamp:1};
	colTweets.find(obj).sort(sort).limit(1).toArray( function(err,res){

		//console.log(res)
		if(err) console.error(err);
		
		if(res.length< 1){
			//we don't have any tweets that haven't been 
			//played so lets get something that hasn't played in a while
			var new_obj = {play_count: { $gte: 1 }};
			var new_sort = {play_count: 1, last_played:1 };
			colTweets.find(new_obj).sort(new_sort).limit(1).toArray( function(err,res){
					//console.log(res);
					callback(res[0]);
			});
			
		}else{
			
			//we have our tweet
			callback(res[0]);
			
		}
		//console.log(res);
		
	});	
	
	
}

/* HANDLE INCOMING TWEETS */

var processIncomingTweet = function(data) { 
	
	
	if(!data.text) return false;
	if(!data.id_str) return false;
	
	//profanity check
	for (i = 0; i < profanity.length; i++) {
		// Use whole word match regex for things like 'analysis' not testing positive for 'anal'
		if (new RegExp("\\b" + profanity[i] + "\\b", "i").test(data.text)) {
			return false;
		}
	}

	if (data.hasOwnProperty('entities')) {
		
		//get tweet media
		if (data['entities'].hasOwnProperty('media')) {
			//console.log(data)
			//console.log(data.entities.media)
			if(data.entities.media[0].type == 'photo') {
				//console.log('Has Photo');
				//can use tweet image for something?
				var media = data.entities.media[0].media_url;
			}
		
		}
		if (data.entities.urls.length>0) {
			
			//console.log(data.entities.urls)
			// we don't want these urls - we just want to ignore them
		
		}
	}
	//find hyperlink image/vine? Could be nice to showcase these in the space in the future
	
	//format retweets
	//@ == AT
	//RT == ReTweet
	//http://*****  == hyperlink
	
	//should add search for special words & easter eggs
	
	
	var incomingText = S(data.text).collapseWhitespace().s;
	
	//remove pesky emoticons from twitter string with REGEX expression 
	//to take out all UTF8 characters in the emoticon range
	//this needs some work
	
	//matty fel fel's solution
	var rawText = incomingText.replace(/[^\x00-\x7f]|[\x80-\xad]/g,"");
	
	console.log("[RAW TEXT] ".error+rawText);
	
	//make the message more audible
	var $text = rawText; //rawText.replace(/\s+/g, '');
	var atext = S($text).replaceAll('\'', '');
	var btext = S(atext).replaceAll('\"', '');
	var ctext = S(btext).replaceAll('\“', '');
	var dtext = S(ctext).replaceAll('@', ' at ');
	var etext = S(dtext).replaceAll('RT', ' retweet ');
	var ftext = S(etext).replaceAll('#', ' hashtag ');
	var gtext = S(ftext).replaceAll('&amp;', 'and');
	var htext = S(gtext).replaceAll('&', 'and');
	
	//clean up unneccessary white spaces
	var  text = S(htext).collapseWhitespace();	
	
	var audio; //the string the audio will become
	
	//remove any URLS for the audio
	if( S(text).contains('http://') ){
		var start = text.indexOf('http://');
		var end = text.indexOf(' ', start);
		//console.log('yes'.error);
		//console.log('start '.error+start+' end '.error+end);
		
		var embeddedUrl;
		if(end == -1) embeddedUrl = text.slice(start).s;
		else embeddedUrl = text.slice(start,end).s;
		
		//console.log(embeddedUrl);
		
		audio = text.replace(embeddedUrl, '').s;
		//console.log(audio);
	}else if(S(text).contains('https://') ){
		var start = text.indexOf('https://');
		var end = text.indexOf(' ', start);
		
		var embeddedUrl;
		if(end == -1) embeddedUrl = text.slice(start).s;
		else embeddedUrl = text.slice(start,end).s;
		
		//console.log(embeddedUrl);
		
		audio = text.replace(embeddedUrl, '').s;
		
	}else{
		
		audio = text.s;
	}
	
	console.log("[AUDIO STRING] ".info+audio.data);
	//console.log( JSON.stringify(data) );
	var filepath = "audio/tweet-"+data.id_str+".wav";
	exec("say -v Kathy -r 160 -o "+filepath+" --file-format=WAVE --data-format=alaw \""+audio+"\"", 
		// anonymous function callback
		function(error, stdout,stderr){
			if(error)console.error('error: '.error + error );
			if(stdout)console.log('stdout: '.warn + stdout);
			if(stderr)console.log('stderr: '.error + stderr);
			console.log("[MADE FILE]".info+filepath.data);
			
			//if the file has been created properly log it in the db.
			if(!error && !stderr){
				//create our db tweet object
				var tweet = {};
				if(media) tweet.media = media;
				tweet.incoming_id = data.id_str;
				tweet.incoming_text = rawText; 
				if(data.user.screen_name) tweet.user = data.user.screen_name; // MUST FIX
				tweet.audio_text = audio;
				tweet.audio_file = filepath;
				tweet.timestamp = new Date();
				tweet.play_count = 0;
				tweet.last_played = null;
				
				//store the object into the database
				colTweets.insert(tweet,function(err){
					if(err) console.error(err);
			
				});

			}
			
		}
	);
	
}