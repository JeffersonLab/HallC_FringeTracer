#ifndef myMessenger_h
#define myMessenger_h 1

#include "G4String.hh"
#include "G4UImessenger.hh"

#include "globals.hh"


class MyMagneticField;

class G4UIcmdWithADoubleAndUnit;
class G4UIcommand;
class G4UIdirectory;


//! Messenger class for commands directed to SHMS.
class MySHMSmessenger : public G4UImessenger {
  public:
    //! A constructor.
    MySHMSmessenger(MyMagneticField* fMagField);
    //! A destructor.
    ~MySHMSmessenger();

    //! Sets new value.
    void SetNewValue(G4UIcommand* command, G4String newValues);
    //! Gets current value.
    G4String GetCurrentValue(G4UIcommand* command);

  private:
    //! Pointer to the magnetic field.
    MyMagneticField* fMagneticField;

    //! Directory of the commands.
    G4UIdirectory* SHMSdirectory;
    //! Command for setting SHMS angle.
    G4UIcmdWithADoubleAndUnit* angleCmd;
};


#endif  // myMessenger_h
