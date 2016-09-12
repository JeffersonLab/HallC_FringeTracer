#include "cmdOptions.hh"

#include <algorithm>
#include <iostream>


cmdOptions::InputParser::InputParser(int &argc, char **argv) {
  for (int i=1; i < argc; ++i) this->tokens.push_back(std::string(argv[i]));
}


std::string cmdOptions::InputParser::getCmdOption(const std::string &option) const {
  std::vector<std::string>::const_iterator itr;
  itr = std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr!=this->tokens.end() && ++itr!=this->tokens.end()) {
      return *itr;
  }
  else {
    return "";
  }
}


bool cmdOptions::InputParser::cmdOptionExists(const std::string &option) const {
  return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}


void cmdOptions::printHelp() {
  std::cout << "Command line options:" << std::endl;
  std::cout << "  -h : display this help" << std::endl;
  std::cout << "  -c fname : use `fname` as configuration file" << std::endl;
  std::cout << "             default is `config.txt`" << std::endl;
  std::cout << "  -m fname : use `fname` as macro file for batch mode" << std::endl;
  std::cout << "             default is empty for interactive mode" << std::endl;
}

std::string cmdOptions::getConfigFile(const InputParser& input) {
  std::string fname = input.getCmdOption("-c");
  if (fname=="") fname = "config.txt";
  return fname;
}

std::string cmdOptions::getMacroFile(const InputParser& input) {
  return input.getCmdOption("-m");
}
