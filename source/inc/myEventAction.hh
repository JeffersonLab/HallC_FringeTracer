#ifndef myEventAction_h
#define myEventAction_h 1

#include "myScreenHit.hh"

#include "G4UserEventAction.hh"

#include "globals.hh"


class G4Event;


class MyEventAction : public G4UserEventAction {
  public:
    MyEventAction();
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

  private:
    MyScreenHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;

    G4int fScreenHCID;
};


#endif  // myEventAction_h
