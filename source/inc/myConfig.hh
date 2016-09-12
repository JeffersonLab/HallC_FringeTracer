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


  extern std::string screenHitOutName;
  extern double shmsAngle;

  extern double beamEnergy;
  extern double beamRasterX;
  extern double beamRasterY;

  extern std::vector<MagnetConfig> magnets;

  void loadConfigFile(const std::string& fname);
  void printConfig();
}

#endif  // myConfig_h
