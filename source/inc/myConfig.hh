#ifndef myConfig_h
#define myConfig_h 1

#include <string>
#include <vector>


//! Interface for holding global settings for the simulation.
namespace config {


  //! Holds settings for each magnetic field.
  class MagnetConfig {
    public:
      //! Name of the field.
      std::string name;
      //! File name for the field map.
      std::string fieldMapFile;
      //! Distance between target cs and field map cs (in cm).
      double transLength;
      //! Angle between target cs z-axis and field map center as if SHMS is set 0 deg (in deg).
      double transAlpha0;
      //! Angle between target cs and field map cs z-axes (in deg).
      double transBeta0;
  };


  //! Output file name for screen hit data.
  extern std::string screenHitOutName;
  //! SMHS angle (in deg).
  extern double shmsAngle;

  //! Beam energy (in GeV).
  extern double beamEnergy;
  //! Beam raster size in x (+- in mm).
  extern double beamRasterX;
  //! Beam raster size in y (+- in mm).
  extern double beamRasterY;

  //! Holds configuration for each magnetic field.
  extern std::vector<MagnetConfig> magnets;

  //! Reads in configuration from file.
  void loadConfigFile(const std::string& fname);
  //! Prints configuration to standard out.
  void printConfig();
}

#endif  // myConfig_h
