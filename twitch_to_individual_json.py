import os
#todo

#3)manually add games


#add hours to overall so rob can use it later

if __name__ == '__main__':
    #write header of twitch
    #for all files in totals folder
    for file in os.listdir("output/"):
        if file.endswith(".txt"):
            index = file.find(".txt")
            file = file[:index]
            json_input = open('Visualization/json_input/' + file + '.json', 'w')
            json_time_input = open('Visualization/json_time_input/' + file + '.json', 'w')
            #write streamer header
            json_input.write('{\n"name": "' + file + '",\n "children": [\n');
            json_time_input.write('{\n"data": [\n');
            current_user = ""
            first_emoji = True
            first_time = True
            comma = False
            with open("output/" + file+".txt") as f:
                last_time = ""
                for line in f:
                    #if user
                    if line[0:5] == "user:":
                        #if not first time
                        if (current_user != ""):
                            #write user ending
                            json_input.write('\n]\n},\n')
                            a = 1
                        #write user beginning
                        user = line[6:-1]
                        json_input.write('{\n"name": "' + user + '",\n"children": [\n');
                        json_time_input.write('{\n"name": "' + user + '"},\n');
                        comma = True
                        #set current user
                        current_user = user
                        #set first emoji to true
                        first_emoji = True
                    #emoji
                    elif line[0:5] == "Time:":
                        new_time = line[5:25]
                        if new_time != last_time:
                            if (not first_time):
                                if comma:
                                    json_time_input.seek(-2,1)
                                    json_time_input.write('\n ')
                                json_time_input.write(']},')
                            comma = False
                            first_time = False
                            json_time_input.write('{"time":"' + new_time + '",\n"users": [\n')

                    else:
                        #print(line)
                        index = line.find(" ")
                        emoji = line[:index]
                        count = line[index+1:-1]
                        if first_emoji:
                            #write without comma on previous line
                            json_input.write('{"name": "' + emoji + '", "size": ' + count + '}');
                            first_emoji = False
                        else:
                            #write with comma on previous line
                            json_input.write(',\n{"name": "' + emoji + '", "size": ' + count + '}');
            #write user ending without comma
            json_input.write('\n]\n}')
            #write streamer ending with comma
            json_input.write('\n]\n},\n')
    #write ending and get rid of extra comma
            print(file)
            json_input.seek(-2,1)
            json_input.write('\n\n');
            #json_time_input.seek(-2,1)
            json_time_input.write(']\n\n}]\n}');
