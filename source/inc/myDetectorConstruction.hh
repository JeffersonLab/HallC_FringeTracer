#ifndef myDetectorConstruction_h
#define myDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"


class MyMagneticField;

class G4FieldManager;
class G4VPhysicalVolume;


class MyDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    static MyMagneticField* fMagneticField;
    static G4FieldManager* fFieldMgr;
};

#endif  // myDetectorConstruction_h
