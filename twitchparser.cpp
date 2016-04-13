#include <string>
#include <fstream>
#include <map>
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
  while (std::getline(infile, line))
  {
      //if beginning is Session Start or Session Time
        //if first time.
          //record time
          //Set last date to current
        //if different from last date
          //record the map
          //fill in any missing inbetween dates for data clarity
          //start new date in different
          //update last date to new date
      //else
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

  infile.close();
  return 1;
}
