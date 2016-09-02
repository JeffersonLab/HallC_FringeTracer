#include "myActionInitialization.hh"

#include "myEventAction.hh"
#include "myPrimaryGeneratorAction.hh"
#include "myRunAction.hh"


MyActionInitialization::MyActionInitialization() : G4VUserActionInitialization() {}


MyActionInitialization::~MyActionInitialization() {}


void MyActionInitialization::BuildForMaster() const {
  SetUserAction(new MyRunAction);
}


void MyActionInitialization::Build() const {
  SetUserAction(new MyPrimaryGeneratorAction);
  SetUserAction(new MyEventAction);
  SetUserAction(new MyRunAction);
}
