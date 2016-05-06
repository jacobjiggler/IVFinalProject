Created by Jacob Martin with the partner Robert Rouhani
Thumbnail included on the main page
Actual visualizations inside of the visualization folder. (the html files)
Don't forget to run them in firefox or another browser that supports reading local files in javascript

Our project was the bubble packing visualization utilizing emojis. We displayed data from both facebook groups and twitch channels. We utilized data we scraped from their websites in a d3 visualization.
We organized the data in this format.
Twitch: Channel -> user -> emoji
Facebook: Group -> user -> emoji
We also implemented a zoom functionality to make it easier for viewers to focus if they want to. One the side of the page is a top emoji chart, and a temporal line graph. The temporal line graph displays the usage of emojis by specific users over time, and is linked with the bubble graph. When you click a user in the graph, it updates to show you the relevant temporal data in the line graph.

we spent about 8 hours thinking about the best way to work with the data we already knew we wanted to work with. Another 4 hours doing research around other visualizations of similar data in the past. We spent probably 30-35 hours actually implementing it(I personally am really bad at javascript which didn't help).

All work was completed by Jake and Robert Rouhani. The effort was split 50-50. Rob focused on gathering facebook data, Jake focused on gathering Twitch, and both worked on all matters of implementation after that
