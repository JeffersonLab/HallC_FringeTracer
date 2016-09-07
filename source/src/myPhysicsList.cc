#include "myPhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4StepLimiterPhysics.hh"


MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList() {
  SetVerboseLevel(1);

  // EM physics.
  RegisterPhysics(new G4EmStandardPhysics());
  // Step limiter in magnetic field.
  RegisterPhysics(new G4StepLimiterPhysics());
}


MyPhysicsList::~MyPhysicsList() {}


void MyPhysicsList::SetCuts() {
  G4VUserPhysicsList::SetCuts();
}
