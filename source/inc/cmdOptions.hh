#ifndef cmdOptions_h
#define cmdOptions_h 1

#include <string>
#include <vector>


//! Interface for dealing with command line arguments.
namespace cmdOptions {


  //! A class for parsing command line arguments.
  // Taken from http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c#868894 .
  // author iain
  class InputParser{
    public:
      //! A constructor.
      InputParser(int& argc, char** argv);

      //! Returns a value corresponding to an option.
      std::string getCmdOption(const std::string& option) const;
      //! Checks if the option exists.
      bool cmdOptionExists(const std::string& option) const;

    private:
      //! Holds the tokenized arguments.
      std::vector <std::string> tokens;
  };


  //! Prints help to standard out.
  void printHelp();
  //! Gets the name of the configuration file.
  std::string getConfigFile(const InputParser& input);
  //! Gets the name of the batch mode macro file.
  std::string getMacroFile(const InputParser& input);
}

#endif  // cmdOptions_h
