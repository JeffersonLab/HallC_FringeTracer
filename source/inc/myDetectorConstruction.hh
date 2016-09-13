#ifndef myDetectorConstruction_h
#define myDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"


class MyMagneticField;

class G4FieldManager;
class G4VPhysicalVolume;


//! Class detailing the construction of geometry, detectors and fields.
class MyDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    //! A constructor.
    MyDetectorConstruction();
    //! A destructor.
    virtual ~MyDetectorConstruction();

    //! Constructs geometry.
    virtual G4VPhysicalVolume* Construct();
    //! Constructs sensitive detectors and fields.
    virtual void ConstructSDandField();

  private:
    //! Pointer to magnetic field.
    static MyMagneticField* fMagneticField;
    //! Pointer to field manager.
    static G4FieldManager* fFieldMgr;
};

#endif  // myDetectorConstruction_h
