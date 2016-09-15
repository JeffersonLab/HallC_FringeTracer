#include "myScreenSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include <iostream>


MyScreenSD::MyScreenSD(const G4String& name, const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name), fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}


MyScreenSD::~MyScreenSD() {}


void MyScreenSD::Initialize(G4HCofThisEvent* hitCollection) {
  // According to the documentation, `collectionName` is a protected member of
  // the `G4VSensitiveDetector`. This makes it OK to call `collectionName[0]`
  // to get string for this instance of sensitive detector.
  fHitsCollection = new MyScreenHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hitCollection->AddHitsCollection(hcID, fHitsCollection);
}


G4bool MyScreenSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
  MyScreenHit* newHit = new MyScreenHit();

  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetPos(step->GetPreStepPoint()->GetPosition());
  newHit->SetParticleType(step->GetTrack()->GetParticleDefinition()->GetParticleName());
  newHit->SetCopyNo(step->GetPreStepPoint()->GetTouchable()->GetCopyNumber());

  fHitsCollection->insert(newHit);

  return true;
}


void MyScreenSD::EndOfEvent(G4HCofThisEvent*) {
  if (verboseLevel>1) {
    G4int nofHits = fHitsCollection->entries();
    G4cout
      << G4endl
      << "-------->Hits Collection: in this event there are " << nofHits
      << " hits in the tracker chambers: " << G4endl;
    for (G4int i=0; i<nofHits; i++) (*fHitsCollection)[i]->Print();
  }
}
