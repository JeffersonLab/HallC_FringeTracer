#ifndef myConfig_h
#define myConfig_h 1


#include <string>
#include <vector>


namespace config {


  class MagnetConfig {
    public:
      std::string name;
      std::string fieldMapFile;
      double transLength;
      double transAlpha0;
      double transBeta0;
  };


  extern double shmsAngle;

  extern double beamEnergy;
  extern double beamRasterX;
  extern double beamRasterY;

  extern std::vector<MagnetConfig> magnets;

  void loadConfigFile();
  void printConfig();
}

#endif  // myConfig_h
