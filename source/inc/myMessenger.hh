#ifndef myMessenger_h
#define myMessenger_h 1

#include "G4String.hh"
#include "G4UImessenger.hh"

#include "globals.hh"


class MyMagneticField;

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
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


//! Messenger class for commands directed to detectors.
class MyDetMessenger : public G4UImessenger {
  public:
    //! A constructor.
    MyDetMessenger();
    //! A destructor.
    ~MyDetMessenger();

    //! Sets new value.
    void SetNewValue(G4UIcommand* command, G4String newValues);
    //! Gets current value.
    G4String GetCurrentValue(G4UIcommand* command);

  private:
    //! Directory of the commands.
    G4UIdirectory* detDirectory;
    //! Command for setting output name for csv files.
    G4UIcmdWithAString* nameCmd;
};


#endif  // myMessenger_h
