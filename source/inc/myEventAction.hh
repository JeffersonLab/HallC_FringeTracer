#ifndef myEventAction_h
#define myEventAction_h 1

#include "myScreenHit.hh"

#include "G4UserEventAction.hh"

#include "globals.hh"


class G4Event;


//! Class detailing actions for each event.
class MyEventAction : public G4UserEventAction {
  public:
    //! A constructor.
    MyEventAction();
    //! A destructor.
    virtual ~MyEventAction();

    //! Action ran at the beginning of an event.
    virtual void BeginOfEventAction(const G4Event*);
    //! Action ran at the end of an event.
    virtual void EndOfEventAction(const G4Event*);

  private:
    //! Gets the collection of hits in a sensitive detector.
    MyScreenHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;

    //! Hit collection ID for beam dump screen.
    G4int fScreenHCID;
    G4int fBpmHCID;
};


#endif  // myEventAction_h
