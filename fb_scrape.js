// Make sure you have the Facebook API installed globally, or move the Node.js stuff out to a separate folder.
// npm install -g fb

//imports
var fs = require('fs');
var FB = require('fb');

if (process.argv.length != 4) {
	console.log("USAGE: nodejs fb_scrape [MAX POSTS] [GROUP ID]")
	return;
}

//output data buffer
var outdata = { users: [] };
var cur_posts = 0;
var max_posts = process.argv[2];
var group_id = process.argv[3]; //"759985267390294";

function parseFb(response) {
	if (!response || response.error) {
		console.log(!response ? 'unknown error' : response.error);
	}
	
	console.log("Parsing response...");
	
	//iterate through each message in the response
	response.data.forEach(function(message) {
		if (message.message === undefined)		//skip what I assume are deleted messages. Some messages in /feed end up just being a timestamp and a unique ID, we don't want those
			return;
		
		cur_posts += 1;
		
		//sorting by user, so see if the user is currently 
		var userFound = outdata.users.filter(function(i) {
			return i.id == message.from.id;
		})[0];
		
		//either append to the existing user id, or generate a new user with a single message in it.
		if (userFound === undefined) {
			outdata.users.push({id: message.from.id, messages: [ {message: message.message, time: message.updated_time, id: message.id} ]});
		}
		else {
			userFound.messages.push({message: message.message, time: message.updated_time, id: message.id});
		}
	});
	
	console.log(cur_posts + " / " + max_posts);
	
	if (cur_posts < max_posts)
	{
		console.log("Making FB request...");
		//console.log(response.paging.next);
		FB.api(
			'/' + group_id + '/feed',
			{fields: ['id','message','updated_time','from'], limit: 1000, offset: cur_posts},
			parseFb);
		return;
	}
	else
	{
		console.log("Writing to file...");
		
		//Write out to a file
		fs.writeFile("./fb_data/" + group_id + ".json", JSON.stringify(outdata, null, 4), function(err) {
			if (err) {
				return console.log(err);
			}
			
			console.log("File saved");
		});
	}
}

console.log("Making FB request...");

//Get a token (and explore the API) here: https://developers.facebook.com/tools/explorer/
FB.setAccessToken('EAACEdEose0cBACAoa1gv5eNuyhlPSVM2ZCwehlXsbtzZCXbZB6i5ekzN5ROksQTkSUQEIZCcrJA4f1XtL7q474EbVmu1K3ZC1jlz0rqMSsjAibTRNCx6cxvnQE4EhkEQC8ZCUXzX9LBezefGDQ0pQJNPW07klAk56RBAfEOyJ66gZDZD');

FB.options({version: 'v2.6'});

//Start making a facebook request
FB.api(
	'/' + group_id + '/feed',
	{fields: ['id','message','updated_time','from'], limit: 1000},
	parseFb
);