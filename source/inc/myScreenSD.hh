#ifndef myScreenSD_h
#define myScreenSD_h 1

#include "G4VSensitiveDetector.hh"

#include "globals.hh"

#include "myScreenHit.hh"


class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;


//! Class detailing beam dump screen sensitive detector.
class MyScreenSD : public G4VSensitiveDetector {
  public:
    //! A constructor.
    MyScreenSD(const G4String& name, const G4String& hitsCollectionName);
    //! A destructor.
    virtual ~MyScreenSD();

    //! Initializes sensitive detector.
    virtual void Initialize(G4HCofThisEvent* hitCollection);
    //! Processes a hit.
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    //! Gets ran at the end of the event.
    virtual void EndOfEvent(G4HCofThisEvent*);

  private:
    //! Pointer to hits collection in the beam dump screen.
    MyScreenHitsCollection* fHitsCollection;
};

#endif  // myScreenSD_h
