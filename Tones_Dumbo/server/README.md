Node.js Server for pulling tweets and creating audio files.

Steps to Running:

	1. Make sure you have Node.js and NPM Installed
		
	1a. Make sure Forever is installed 

		 $ [sudo] npm install forever -g		

	2. Create Audio Folder

		$ cd server
		$ mkdir audio

	3. Get necessary add-ons

		$ cd server
		$ npm install
			
	4. Run Node.js Server natively
		
		$ node server/twitter.js

	5. BEST Option Run Server through Forever
		
		$ forever start -a -o twitterOut.log -l twitter.log -e twitterError.log twitter.js

		 
		

Notes:

	/server folder must contain an /audio folder
	
	You must run the code from within the /server folder otherwise you'll get audio creation errors.
		
	immortal-ntwitter must be downloaded seperately from NPM 

	View the log file from node.js/Forever:
		$ tail -f ~/.forever/twitter.log	

	Credentials have not been seperated out, however multiple versions of this code cannot run at the same time yet as immortal-ntwitter will compete we will migrate to two running stable versions soon and provide key.js files to ensure this
