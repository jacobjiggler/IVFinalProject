Robert Rouhani
(partnered with Jacob Martin)

					Differing emoji utilization across communities final report

 - Thumbnail included as /thumbnail.png
 - Visualization included in /Visualization/emoji.html
 - If running on Firefox, you can use the file:// protocol to open the file, otherwise run a local server (e.g. `python -m SimpleHTTPServer`)
 - Helper scripts and intermediate scraping data included throughout the rest of the root folder.

We visualized emoji use within communities as a graph of enclosed circles, for individual emoji, users, Twitch channels/Facebook groups, and finally entire websites (Twitch/Facebook).
The visualization includes zoom functionality to help navigate very large datasets.
 
The amount of time spent on this project can be roughly split into the following:

 - 8 hours planning out how data should be formatted and stored
 - 4 hours researching similar visualizations
 - 30-35 hours of raw implementation (and learning how to use node js and brushing up my client side js)
 
We split the work about evenly. I foced on Facebook data gathering while Jake focused on Twitch. We both worked on the implementation and frontend after that.

Changing datasets are done by modifying emoji.html to change both lines of d3.json("json_*", *) to valid files in the respective folders.
