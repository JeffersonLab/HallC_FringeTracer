#include "myPhysicsList.hh"

#include "G4EmStandardPhysics.hh"


MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList() {
  SetVerboseLevel(1);

  // EM physics.
  RegisterPhysics(new G4EmStandardPhysics());
}


MyPhysicsList::~MyPhysicsList() {}


void MyPhysicsList::SetCuts() {
  G4VUserPhysicsList::SetCuts();
}
