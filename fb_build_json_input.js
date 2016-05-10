var fs = require('fs');
var csv_parse = require('csv-parse');

if (process.argv.length < 4)
{
	console.log("USAGE: nodejs fb_build_json_input.js [IN FILE] [OUT FILE]");
	return;
}

var in_file_name = process.argv[2];
var out_file_name = process.argv[3];

var outfb = JSON.parse(fs.readFileSync(in_file_name, 'utf8'));
var emoji_dict = {};

var base_emoji_parser = csv_parse(fs.readFileSync('fb-emoticons.csv', 'utf8'), { delimiter: ',', quote: '7', relax_column_count: true}, function(err, data) {
        if (err) throw err;
        for (var emoji_idx in data) {
            var emoji = data[emoji_idx];
            for (var i = 1; i < emoji.length; i += 1) {
                emoji_dict[emoji[i]] = emoji[0];
            }
        }
});

base_emoji_parser.on('end', function() {
    //console.log(emoji_dict);
    var out_json = { name: "Hackathon Hackers", children: [] };
    var out_emoji_dict = {};

    for (var user_idx in outfb.users) {
        var user = outfb.users[user_idx];
        var user_node = { name: user.id, children: [] };
        var user_emoji_dict = {};
        for (var user_message_idx in user.messages) {
            var user_message = user.messages[user_message_idx].message;
            for (var emoji in emoji_dict) {
				var emoji_str_index = user_message.indexOf(emoji);
                if (emoji_str_index != -1) {
					
					//a limitation of this technique are links, http:// contains :/ which is the "unsure" emoji.
					if (user_message.substring(emoji_str_index - 4, emoji_str_index) == "http" || user_message.substring(emoji_str_index - 5, emoji_str_index) == "https") {
						console.log("skipping link");
						continue;
					}
					
					console.log(user_message.substring(emoji_str_index - 5, emoji_str_index + 5));
					
                    var emoji_name = emoji_dict[emoji];
                    if (user_emoji_dict.hasOwnProperty(emoji_name))
                        user_emoji_dict[emoji_name] += 1;
                    else
                        user_emoji_dict[emoji_name] = 1;
                }
            }
        }
        
        if (Object.keys(user_emoji_dict).length == 0)
            continue;
        
        for (var user_emoji in user_emoji_dict) {
            user_node.children.push({name: user_emoji, size: user_emoji_dict[user_emoji]});
        }
        
        out_json.children.push(user_node);
    }
    
    //for (var out_emoji in out_emoji_dict) {
      //      out_json.children.push({name: out_emoji, size: out_emoji_dict[out_emoji]});
        //}

    fs.writeFileSync(out_file_name, JSON.stringify(out_json, null, '\t'));
});
