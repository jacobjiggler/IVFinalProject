import os
import json
import ast
max_filesize = 50000


if __name__ == '__main__':
    #write header of twitch
    #for all files in totals folder
    for file in os.listdir("Visualization/json_input/"):
        if file.endswith(".json"):
            index = file.find(".json")
            file_size = os.path.getsize("Visualization/json_input/" + file)
            file = file[:index]
            total = 0
            json_min_input = open('Visualization/json_min_input/' + file + '.json', 'w+')
            with open('Visualization/json_input/' + file + '.json') as data_file:
                data = json.load(data_file)
                print len(data['children'])
                count_max = len(data['children'])
                if (count_max > 20):
                    i = 0
                    while i < count_max:
                        total += len(data['children'][i]['children'])
                        i+=1
                    average = total / len(data['children'])
                    print average
                    #remove
                    count_max = len(data['children'])
                    i = 0
                    while i < count_max:
                        total += len(data['children'][i]['children'])
                        if (len(data['children'][i]['children']) <= average):
                            data['children'].pop(i)
                            count_max = count_max - 1
                            i-=1
                        else:
                            a = 0
                        i+=1
                    print len(data['children'])
                    output = json.dumps(data)
                    json_min_input.write(output)
                    print ("file size before: " +  str(file_size) + ", file size after: " + str(os.path.getsize("Visualization/json_min_input/" + file + ".json")))
