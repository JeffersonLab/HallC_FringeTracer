#ifndef myEventAction_h
#define myEventAction_h 1

#include "G4UserEventAction.hh"


class G4Event;


class MyEventAction : public G4UserEventAction {
  public:
    MyEventAction();
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
};


#endif  // myEventAction_h
