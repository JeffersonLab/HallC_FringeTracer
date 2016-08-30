#ifndef myDetectorConstruction_h
#define myDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class G4VPhysicalVolume;


class myDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    myDetectorConstruction();
    virtual ~myDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif  // myDetectorConstruction_h
