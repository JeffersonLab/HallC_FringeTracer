#ifndef cmdOptions_h
#define cmdOptions_h 1

#include <string>
#include <vector>

namespace cmdOptions {


  // Taken from http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c#868894 .
  // author iain
  class InputParser{
    public:
      InputParser(int &argc, char **argv);

      std::string getCmdOption(const std::string &option) const;
      bool cmdOptionExists(const std::string &option) const;

    private:
      std::vector <std::string> tokens;
  };


  void printHelp();
  std::string getConfigFile(const InputParser& input);
  std::string getMacroFile(const InputParser& input);

}

#endif  // cmdOptions_h
