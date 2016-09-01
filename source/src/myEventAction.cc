#include "myEventAction.hh"

#include "G4Event.hh"
#include "G4ios.hh"


MyEventAction::MyEventAction() : G4UserEventAction() {}


MyEventAction::~MyEventAction() {}


void MyEventAction::BeginOfEventAction(const G4Event*) {}


void MyEventAction::EndOfEventAction(const G4Event* anEvent) {}
