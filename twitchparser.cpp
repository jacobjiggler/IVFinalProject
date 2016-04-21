#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
#include <sstream>
#include <algorithm>

typedef std::map<std::string, int> twitch_emojis;
typedef std::map<std::string, twitch_emojis > twitch_users;


//possibly change to work by hour instead

void record(twitch_users &users, twitch_users &user_totals, std::ofstream& outfile){
  for(twitch_users::iterator it_users = users.begin(); it_users != users.end(); it_users++) {
    std::string temp_user = "user: " + it_users->first + "\n";
    //if user used any emojis
    if (it_users->second.size() > 0)
    {
      outfile<<temp_user;

      //if not in  user_totals
      twitch_emojis* totals;
      if (user_totals.find(it_users->first) == user_totals.end()){
        twitch_emojis emojis;
        user_totals[it_users->first] = emojis;
      }
      totals = &user_totals[it_users->first];

      for(twitch_emojis::iterator it_emojis = it_users->second.begin(); it_emojis != it_users->second.end(); it_emojis++) {
        std::stringstream ss;
        ss << it_emojis->first <<  " " << it_emojis->second  << "\n";
        std::string temp_emoji = ss.str();
        outfile << temp_emoji;
        //if not in totals
        if (totals->find(it_emojis->first)==totals->end()){
          (*totals)[it_emojis->first] = it_emojis->second;
        }
        else {
          (*totals)[it_emojis->first]+=it_emojis->second;
        }
      }
      it_users->second.clear();
    }
  }
  users.clear();


}
void recordtotals(twitch_users &user_totals, std::ofstream& totaloutfile){
  for(twitch_users::iterator it_users = user_totals.begin(); it_users != user_totals.end(); it_users++) {
    //print user
    std::string temp_user = "user: " + it_users->first + "\n";
    totaloutfile<<temp_user;
    for(twitch_emojis::iterator it_emojis = it_users->second.begin(); it_emojis != it_users->second.end(); it_emojis++) {
      std::stringstream ss;
      ss << it_emojis->first <<  " " << it_emojis->second  << "\n";
      std::string temp_emoji = ss.str();
      totaloutfile << temp_emoji;
    }
  }
}

main(int argc, char *argv[])
{
    //load in master set of emojis
    std::map<std::string,std::string> master_set;
    twitch_users totals;
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
    std::string totalfilename = "total_";
    outfilename.append("_output.txt");
    totalfilename.append(outfilename);
    totalfilename.insert(0,"total/");
    outfilename.insert(0,"output/");
    std::ofstream outfile;
    outfile.open(outfilename.c_str());
    std::ofstream totaloutfile;
    totaloutfile.open(totalfilename.c_str());
    std::tm  last_date;
    twitch_users users;
    bool first_run = true;
    int count = 0;
    while (std::getline(infile, line))
    {
        //if date declaration
        if (line.substr(0,12)=="Session Time" || line.substr(0,13) == "Session Start")
        {
            std::tm date;
            std::string temp_date;
            if (line.substr(13,1) == ":") {
                temp_date = line.substr(15,24);
            }
            else {
                temp_date = line.substr(14,24);
            }
            if (strptime(temp_date.c_str(), "%a %b %d %H:%M:%S %Y", &date)==NULL)
                std::cout << "error" << std::endl;

            date.tm_isdst = -1;

            //if first time.
            if (first_run) {

                //record time
                char buffer [80];
                if (strftime (buffer,80,"Time: %a %b %d 00:00:00 %Y\n",&date)<=0)
                    std::cout << "strf Error" << std::endl;
                //set to beginning of day
                if (strptime(temp_date.c_str(), "%a %b %d %H:%M:%S %Y", &date)==NULL)
                    std::cout << "strp error" << std::endl;
                outfile<<buffer;
                //Set last date to current
                last_date = date;
                first_run = false;
                continue;
            }


            //if different from last date
            if ( date.tm_mday != last_date.tm_mday || date.tm_mon != last_date.tm_mon || date.tm_year != last_date.tm_year)
            {

                //record the map
                record(users,totals, outfile);


                //fill in any missing inbetween dates for data clarity
                //add 1 to tm_mday of last_date and write until on new day
                last_date.tm_mday +=1;

                while(date.tm_mday != last_date.tm_mday || date.tm_mon != last_date.tm_mon || date.tm_year != last_date.tm_year)
                {
                  char buffer [80];
                  if (strftime (buffer,80,"Time: %a %b %d 00:00:00 %Y\n",&last_date)<=0)
                      std::cout << "strf Error" << std::endl;
                  outfile<<buffer;
                  last_date.tm_mday +=1;
              }
              //print new date
              char buffer [80];
              if (strftime (buffer,80,"Time: %a %b %d 00:00:00 %Y\n",&date)<=0)
                  std::cout << "strf Error" << std::endl;
              outfile<<buffer;
                //update last date to new date
                last_date = date;

            }
        }
        else {
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
                        //check if emojii in master_set
                        if (master_set.find(word) != master_set.end()) {
                          std::string temp_word = master_set.find(word)->second;
                          //if emojii in map
                          twitch_emojis::iterator it = (user_it->second).find(temp_word);
                          if (it != (user_it->second).end()) {

                              //increment
                              it->second++;
                              //std::cout<< it->second << std::endl;
                          }
                          else
                          {

                                //add emojii set to 1
                                (user_it->second)[temp_word] = 1;
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
                          std::string temp_word = master_set.find(word)->second;
                            //if emoji in map
                            twitch_emojis::iterator it = users[user].find(temp_word);
                            if (it != emojis.end()) {
                                //increment
                                users.find(user)->second[temp_word]++;

                            }
                            else {
                                //add emoji to map
                                users.find(user)->second[temp_word] = 1;

                            }
                        }
                    }


                }


            }
        }
    }
    //record one last time because it might not have been called earlier
    record(users,totals, outfile);
    //delete last_date;
    //record totals
    recordtotals(totals,totaloutfile);
    infile.close();
    outfile.close();
    return 0;
}
