#ifndef myMessenger_h
#define myMessenger_h 1

#include "G4UImessenger.hh"

#include "globals.hh"


class G4UIcmdWithADoubleAndUnit;
class G4UIcommand;
class G4UIdirectory;


class MySHMSmessenger : public G4UImessenger {
  public:
    MySHMSmessenger();
    ~MySHMSmessenger();

    void SetNewValue(G4UIcommand* command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand* command);

  private:
    G4UIdirectory* SHMSdirectory;

    G4UIcmdWithADoubleAndUnit* angleCmd;
};



#endif  // myMessenger_h
