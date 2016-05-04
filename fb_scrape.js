// Make sure you have the Facebook API installed globally, or move the Node.js stuff out to a separate folder.
// npm install -g fb

//imports
var fs = require('fs');
var FB = require('fb');

//output data buffer
var outdata = { users: [] };

console.log("Making FB request...");

//Get a token (and explore the API) here: https://developers.facebook.com/tools/explorer/
FB.setAccessToken('');

//Start making a facebook request
FB.api(
	'/759985267390294/feed',
	'GET',
	{"fields":"id,message,updated_time,from", "limit": "1000"},
	function (response) {

		console.log("Parsing response...");
	
		//iterate through each message in the response
		response.data.forEach(function(message) {
			if (message.message === undefined)		//skip what I assume are deleted messages. Some messages in /feed end up just being a timestamp and a unique ID, we don't want those
				return;
			
			//sorting by user, so see if the user is currently 
			var userFound = outdata.users.filter(function(i) {
				return i.id == message.from.id;
			})[0];
			
			//either append to the existing user id, or generate a new user with a single message in it.
			if (userFound === undefined) {
				outdata.users.push({id: message.from.id, messages: [ {message: message.message, time: message.time, id: message.id} ]});
			}
			else {
				userFound.messages.push({message: message.message, time: message.time, id: message.id});
			}
		});
		
		console.log("Writing to file...");
		
		//Write out to a file
		fs.writeFile("./OUTFB.json", JSON.stringify(outdata, null, 4), function(err) {
			if (err) {
				return console.log(err);
			}
			
			console.log("File saved");
		});
	}
);