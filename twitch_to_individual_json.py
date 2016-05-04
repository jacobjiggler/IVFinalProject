import os
#todo

#3)manually add games


#add hours to overall so rob can use it later

if __name__ == '__main__':
    #write header of twitch
    #for all files in totals folder
    for file in os.listdir("total/"):
        if file.endswith(".txt"):
            index = file.find(".txt")
            file = file[:index]
            jsonfile = open('Visualization/json_input' + file + '.json', 'w')
            #write streamer header
            jsonfile.write('{\n"name": "' + file + '",\n "children": [\n');
            current_user = ""
            first_emoji = True
            with open("total/" + file+".txt") as f:
                for line in f:
                    #if user
                    if line[0:5] == "user:":
                        #if not first time
                        if (current_user != ""):
                            #write user ending
                            jsonfile.write('\n]\n},\n')
                            a = 1
                        #write user beginning
                        user = line[6:-1]
                        jsonfile.write('{\n"name": "' + user + '",\n"children": [\n');
                        #set current user
                        current_user = user
                        #set first emoji to true
                        first_emoji = True
                    #emoji
                    else:
                        index = line.find(" ")
                        emoji = line[:index]
                        count = line[index+1:-1]
                        if first_emoji:
                            #write without comma on previous line
                            jsonfile.write('{"name": "' + emoji + '", "size": ' + count + '}');
                            first_emoji = False
                        else:
                            #write with comma on previous line
                            jsonfile.write(',\n{"name": "' + emoji + '", "size": ' + count + '}');
            #write user ending without comma
            jsonfile.write('\n]\n}')
            #write streamer ending with comma
            jsonfile.write('\n]\n},\n')
    #write ending and get rid of extra comma
            print(file)
            jsonfile.seek(-2,1)
            jsonfile.write('\n\n');
