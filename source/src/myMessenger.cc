#include "myMessenger.hh"

#include "myConfig.hh"
#include "myMagneticField.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

#include <iostream>


MySHMSmessenger::MySHMSmessenger(MyMagneticField* fMagField)
: fMagneticField(fMagField)
{
  // Set SHMS commands directory.
  SHMSdirectory = new G4UIdirectory("/SHMS/");
  SHMSdirectory->SetGuidance("SHMS control commands.");

  // Set command for setting SHMS angle.
  angleCmd = new G4UIcmdWithADoubleAndUnit("/SHMS/angle", this);
  angleCmd->SetGuidance("Set angle of spectrometer.");
  angleCmd->SetParameterName("th", true, true);
  angleCmd->SetDefaultUnit("deg");
  angleCmd->SetUnitCandidates("deg rad mrad");
  angleCmd->SetRange("th >= 5.5");
}


MySHMSmessenger::~MySHMSmessenger() {
  delete angleCmd;
  delete SHMSdirectory;
}


void MySHMSmessenger::SetNewValue(G4UIcommand* command, G4String newValues) {
  if (command==angleCmd) {
    // Set value of angle in the global config and update the field.
    config::shmsAngle = angleCmd->GetNewDoubleValue(newValues)/deg;
    fMagneticField->updateField();
  }
}


G4String MySHMSmessenger::GetCurrentValue(G4UIcommand* command) {
  G4String cv;

  if (command==angleCmd) {
    cv = angleCmd->ConvertToString(config::shmsAngle);
  }

  return cv;
}
