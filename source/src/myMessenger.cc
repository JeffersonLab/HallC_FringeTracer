#include "myMessenger.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

#include <iostream>


MySHMSmessenger::MySHMSmessenger() {
  SHMSdirectory = new G4UIdirectory("/SHMS/");
  SHMSdirectory->SetGuidance("SHMS control commands.");

  angleCmd = new G4UIcmdWithADoubleAndUnit("/SHMS/angle", this);
  angleCmd->SetGuidance("Set angle of spectrometer.");
  angleCmd->SetParameterName("th", true, true);
  angleCmd->SetDefaultUnit("deg");
  angleCmd->SetUnitCandidates("deg rad mrad");
  angleCmd->SetRange("th >= 5.5");
}


MySHMSmessenger::~MySHMSmessenger() {
  delete SHMSdirectory;
}


void MySHMSmessenger::SetNewValue(G4UIcommand* command, G4String newValues) {}


G4String MySHMSmessenger::GetCurrentValue(G4UIcommand* command) {return "blah";}
