#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
typedef std::map<std::string, int> emojis;
typedef std::map<std::string, emojis > users;
//todo
//1)implement commented pseudocode
//2)change to output to working json
//3)change to work by hour instead
main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  std::string outfilename = argv[1];
  outfilename.append("_output.txt");
  std::ofstream outfile(outfilename.c_str());
  std::string line;
  std::tm last_date = {};
  bool first_run = false;
  while (std::getline(infile, line))
  {
    //if date declaration
    if (line.substr(0,12)=="Session Time" || line.substr(0,13) == "Session Start")
    {
        std::tm date = {};
        std::string temp_date;
        if (line.substr(13,1) == ":"){
          temp_date = line.substr(14,10);
          std::cout << temp_date << std::endl;
        }
        else {
          temp_date = line.substr(13,10);
        }
        strptime(temp_date, "%a %b %d", &date);
        //if first time.
        if (first_run){
          //record time
          //Set last date to current
          first_run = false;
        }
        //if different from last date
          //record the map
          //fill in any missing inbetween dates for data clarity
          //start new date in different
          //update last date to new date
              }
      else {
        //if beginning is [ and ] < afterwards
          //if user in map
            //if emojii in map
              //increment
            //else
              //add emojii set to 1
          //else
            //create emojii map with new emojii set to 1
            //set user to emojii map
        //else
          //error?
        }
  }

  infile.close();
  return 1;
}
