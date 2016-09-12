#include "myConfig.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


namespace config {
  std::string screenHitOutName = "out";
  double shmsAngle = 5.5;

  double beamEnergy = 11.0;
  double beamRasterX = 4.0;
  double beamRasterY = 4.0;

  std::vector<MagnetConfig> magnets;
}


void config::loadConfigFile(const std::string& fname) {
  std::ifstream ifs(fname);

  std::string line;
  std::string item;

  if (ifs.is_open()) {

    while (getline(ifs, line)) {
      if (line.empty()) continue;

      std::vector<std::string> tokens;

      std::stringstream ss;
      ss.str(line);

      while(getline(ss, item, ' ')) {
        if (!item.empty()) tokens.push_back(item);
      }

      if (tokens[0][0] == '#') continue;

      // General settings.
      if (tokens[0] == "screenHit.outName") {
        config::screenHitOutName = tokens[2];
      }
      else if (tokens[0] == "shms.angle") {
        config::shmsAngle = std::atof(tokens[2].c_str());
      }
      // Beam settings.
      else if (tokens[0] == "beam.energy") {
        config::beamEnergy = std::atof(tokens[2].c_str());
      }
      else if (tokens[0] == "beam.raster.x") {
        config::beamRasterX = std::atof(tokens[2].c_str());
      }
      else if (tokens[0] == "beam.raster.y") {
        config::beamRasterY = std::atof(tokens[2].c_str());
      }
      // Definitions of magnetic fields.
      else if (tokens[0] == "magnet.name") {
        config::magnets.push_back(config::MagnetConfig());
        config::magnets.back().name = tokens[2];
      }
      else if (tokens[0] == "magnet.fieldMap") {
        config::magnets.back().fieldMapFile = tokens[2];
      }
      else if (tokens[0] == "magnet.trans.l") {
        config::magnets.back().transLength = std::atof(tokens[2].c_str());
      }
      else if (tokens[0] == "magnet.trans.alpha0") {
        config::magnets.back().transAlpha0 = std::atof(tokens[2].c_str());
      }
      else if (tokens[0] == "magnet.trans.beta0") {
        config::magnets.back().transBeta0 = std::atof(tokens[2].c_str());
      }
      // Others.
      else std::cout << "Unknown keyword " << tokens[0] << "!" << std::endl;
    }
  }

  ifs.close();
}


void config::printConfig() {
  std::cout << "General settings:" << std::endl;
  std::cout << "  Screen hit output file name: " << config::screenHitOutName << std::endl;
  std::cout << "  SHMS angle: " << config::shmsAngle << "deg" << std::endl;
  std::cout << std::endl;
  std::cout << "Beam settings:" << std::endl;
  std::cout << "  beam energy: " << config::beamEnergy << "GeV" << std::endl;
  std::cout << "  beam raster x: +-" << config::beamRasterX << "mm" << std::endl;
  std::cout << "  beam raster y: +-" << config::beamRasterY << "mm" << std::endl;
  std::cout << std::endl;
  if (config::magnets.size() > 0) {
    std::cout << "Magnetic fields:" << std::endl;
    for (size_t i=0; i<config::magnets.size(); ++i) {
      std::cout << "  Field " << i << std::endl;
      std::cout << "    name: " << config::magnets[i].name << std::endl;
      std::cout << "    field map file: " << config::magnets[i].fieldMapFile << std::endl;
      std::cout << "    translation length: " << config::magnets[i].transLength << std::endl;
      std::cout << "    translation alpha0: " << config::magnets[i].transAlpha0 << std::endl;
      std::cout << "    translation beta0: " << config::magnets[i].transBeta0 << std::endl;
    }
  }
}
