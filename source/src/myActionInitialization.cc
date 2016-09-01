#include "myActionInitialization.hh"

#include "myEventAction.hh"
#include "myPrimaryGeneratorAction.hh"


MyActionInitialization::MyActionInitialization() : G4VUserActionInitialization() {}


MyActionInitialization::~MyActionInitialization() {}


void MyActionInitialization::BuildForMaster() const {}


void MyActionInitialization::Build() const {
  SetUserAction(new MyPrimaryGeneratorAction);
  SetUserAction(new MyEventAction);
}
