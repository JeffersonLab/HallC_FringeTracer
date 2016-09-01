#ifndef myDetectorConstruction_h
#define myDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"


class G4GlobalMagFieldMessenger;
class G4VPhysicalVolume;


class MyDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    static G4GlobalMagFieldMessenger* fMagFieldMessenger;
};

#endif  // myDetectorConstruction_h
