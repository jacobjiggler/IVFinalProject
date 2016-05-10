var fs = require('fs');
var csv_parse = require('csv-parse');

var emoji_list = [];

var base_emoji_parser = csv_parse(fs.readFileSync('fb-emoticons.csv', 'utf8'), { delimiter: ',', quote: '7', relax_column_count: true}, function(err, data) {
        if (err) throw err;
        for (var emoji_idx in data) {
            var emoji = data[emoji_idx];
            emoji_list.push({name: emoji[0]});
        }
});

base_emoji_parser.on('end', function() {
    fs.writeFileSync('fb_emoji_list.json', JSON.stringify(emoji_list, null, '\t'));
});
