import os
#todo

#3)manually add games



if __name__ == '__main__':
    #write header of twitch
    #for all files in totals folder
    for file in os.listdir("output/"):
        if file.endswith(".txt"):
            index = file.find(".txt")
            file = file[:index]
            json_time_input = open('Visualization/json_time_input/' + file + '.json', 'w+')
            #write streamer header
            json_time_input.write('{\n"data": [\n');
            new_time = ""
            first_line = True
            with open("output/" + file+".txt") as f:
                last_time = ""
                while True:
                    line = f.readline()
                    if not line: break
                    #if user
                    if line[0:5] == "user:":
                        if not firstline:
                            #remove previous comma if it's there and close the last user
                            json_time_input.seek(-2,1)
                            c  = json_time_input.read(1)
                            print(c)
                            if (c == ","):
                                json_time_input.seek(-1,1)
                                json_time_input.write("\n]},\n")

                        #write user beginning
                        user = line[6:-1]
                        json_time_input.write('{"name": "' + user + '", "children": [');
                    #emoji
                    elif line[0:5] == "Time:":
                        new_time = line[5:25]
                        firstline = False
                    else:
                        #print(line)
                        index = line.find(" ")
                        emoji = line[:index]
                        count = line[index+1:-1]
                        #print here
                        json_time_input.write('\n{"name": "' + emoji + '", "time": "' + new_time + '"},\n');

            print(file)
            #remove previous comma if it's there and close the last user
            json_time_input.seek(-2,1)
            c  = json_time_input.read(1)
            print(c)
            if (c == ","):
                json_time_input.seek(-1,1)
                json_time_input.write("\n]}\n")

            json_time_input.write('\n]\n}\n')
            json_time_input.seek(-2,1)
