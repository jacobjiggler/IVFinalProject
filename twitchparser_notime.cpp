#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
#include <sstream>
#include <algorithm>
typedef std::map<std::string, int> twitch_emojis;
typedef std::map<std::string, twitch_emojis > twitch_users;

//ADD TOTALS AT END
//SWITCH TO other BUbble enclosure visualization

//1)implement commented pseudocode
//2)change to output to working json
//3)change to work by hour instead
main(int argc, char *argv[])
{
    //load in master set of emojis
    std::map<std::string,std::string> master_set;
    std::ifstream master_file("emoji_representations.txt");
    std::string line;
    while (std::getline(master_file, line))
    {
        std::size_t found= line.find("	");
        if (found!=std::string::npos)
            master_set[line.substr(0,found)] = line.substr(found + 1, line.length() - found - 1);
        else
            std::cout << "Error" << found << '\n';

    }
    master_file.close();
    std::ifstream infile(argv[1]);
    std::string outfilename = argv[1];
    outfilename.append("_output.txt");
    outfilename.insert(0,"output/");
    std::ofstream outfile;
    outfile.open(outfilename.c_str());
    std::tm * last_date;
    twitch_users users;
    bool first_run = true;
    while (std::getline(infile, line))
    {
        //if beginning is [ and ] < afterwards
        if (!line.empty() && line.substr(0,1)=="[" && line.substr(6,3)=="] <") {
            int pos = line.find("> ");
            std::string user = line.substr(9,pos-9);
            std::string message = line.substr(pos + 2, line.length()-(pos+2));
            //if user in map
            twitch_users::iterator user_it = users.find(user);
            if (user_it != users.end()) {
                //for every word in message
                std::stringstream s(message);
                std::string word;
                while(s >> word) {
                    //make word lowercase
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    //if emojii in map
                    twitch_emojis::iterator it = (user_it->second).find(word);
                    if (it != (user_it->second).end()) {

                        //increment
                        it->second++;
                        std::cout<< it->second << std::endl;
                    }
                    else
                    {
                        //check if emojii in master_set
                        if (master_set.find(word) != master_set.end()) {
                            //add emojii set to 1
                            (user_it->second)[word] = 1;
                        }
                    }
                }
            }
            else {
                //create new emoji map
                twitch_emojis emojis;

                //set user to map
                users[user] = emojis;
                //for every word in message
                std::stringstream s(message);
                std::string word;
                while(s >> word) {
                    //make word lowercase
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    //if emoji in master_set
                    if (master_set.find(word) != master_set.end()) {
                        //if emoji in map
                        twitch_emojis::iterator it = users[user].find(word);
                        if (it != emojis.end()) {
                            //increment
                            users.find(user)->second[word]++;

                        }
                        else {
                            //add emoji to map
                            users.find(user)->second[word] = 1;

                        }
                    }
                }


            }


        }
    }
    infile.close();
    outfile.close();
    return 0;
}
