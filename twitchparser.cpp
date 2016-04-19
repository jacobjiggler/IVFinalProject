#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
typedef std::map<std::string, int> emojis;
typedef std::map<std::string, emojis > users;
//todo

Initially add emoji names from emojii folder to a master map
ADD TOTALS AT END
SWITCH TO other BUbble enclosure visualization
//1)implement commented pseudocode
//2)change to output to working json
//3)change to work by hour instead
main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  std::string outfilename = argv[1];
  outfilename.append("_output.txt");
  std::ofstream outfile;
  outfile.open(outfilename.c_str());

  std::ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  std::string line;
  std::tm * last_date;
  bool first_run = true;
  while (std::getline(infile, line))
  {
    //if date declaration
    if (line.substr(0,12)=="Session Time" || line.substr(0,13) == "Session Start")
    {
        std::tm date;
        std::string temp_date;
        if (line.substr(13,1) == ":"){
          temp_date = line.substr(15,24);
        }
        else {
          temp_date = line.substr(14,24);
        }
        std::cout<<temp_date <<std::endl;
        if (strptime(temp_date.c_str(), "%a %b %d %H:%M:%S %Y", &date)==NULL)
          std::cout << "error" << std::endl;

        date.tm_isdst = -1;
        //time_t date_t = mktime(&date);

        //if first time.
        if (first_run){

          //record time
          char buffer [80];
          if (strftime (buffer,80,"Time: %a %b %d 00:00:00 %Y\n",&date)<=0)
            std::cout << "strf Error" << std::endl;
          //set to beginning of day
          if (strptime(temp_date.c_str(), "%a %b %d %H:%M:%S %Y", &date)==NULL)
            std::cout << "strp error" << std::endl;
          outfile<<buffer;
          //Set last date to current
          last_date = &date;
          first_run = false;
          continue;
        }
        //if different from last date
        char buffer1 [80];
        char buffer2 [80];
        if (strftime (buffer1,80,"%a %b %d %Y",&date)<=0)
          std::cout << "Error1" << std::endl;
        if(strftime (buffer2,80,"%a %b %d %Y",last_date)<=0)
          std::cout << "Error2" << std::endl;
        if ( strcmp(buffer1,buffer2) != 0 )
        {
          //record the map(split into own function)
          //fill in any missing inbetween dates for data clarity
          //start new date in different
          //delete old date
          //update last date to new date
        }
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
  outfile.close();
  return 0;
}
