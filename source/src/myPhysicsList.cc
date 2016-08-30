#include "myPhysicsList.hh"

#include "G4EmStandardPhysics.hh"


myPhysicsList::myPhysicsList() : G4VModularPhysicsList() {
  SetVerboseLevel(1);

  // EM physics.
  RegisterPhysics(new G4EmStandardPhysics());
}


myPhysicsList::~myPhysicsList() {}


void myPhysicsList::SetCuts() {
  G4VUserPhysicsList::SetCuts();
}
