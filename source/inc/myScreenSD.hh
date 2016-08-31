#ifndef myScreenSD_h
#define myScreenSD_h 1

#include "G4VSensitiveDetector.hh"

#include "globals.hh"

#include "myScreenHit.hh"


class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;


class MyScreenSD : public G4VSensitiveDetector {
  public:
    MyScreenSD(const G4String& name, const G4String& hitsCollectionName);
    virtual ~MyScreenSD();

    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void EndOfEvent(G4HCofThisEvent*);

  private:
    MyScreenHitsCollection* fHitsCollection;
};

#endif  // myScreenSD_h
