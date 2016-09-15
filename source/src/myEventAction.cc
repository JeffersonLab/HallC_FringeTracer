#include "myEventAction.hh"

#include "myAnalysis.hh"
#include "myScreenHit.hh"

#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"


MyEventAction::MyEventAction() : G4UserEventAction(), fScreenHCID(-1), fBpmHCID(-1) {}


MyEventAction::~MyEventAction() {}


void MyEventAction::BeginOfEventAction(const G4Event*) {}


void MyEventAction::EndOfEventAction(const G4Event* anEvent) {
  // Assing ID at the first event of the run.
  if (fScreenHCID == -1) {
    fScreenHCID = G4SDManager::GetSDMpointer()->GetCollectionID("bdScreenHC");
  }
  if (fBpmHCID==-1) fBpmHCID = G4SDManager::GetSDMpointer()->GetCollectionID("bpmScreenHC");

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  G4ThreeVector pos;
  G4int particleType;

  // Process events in the beam dump hit collection.
  MyScreenHitsCollection* screenHC = GetHitsCollection(fScreenHCID, anEvent);
  for (int i=0; i<screenHC->entries(); ++i) {
    MyScreenHit* screenHit = (*screenHC)[i];

    pos = screenHit->GetPos();
    particleType = screenHit->GetParticleTypeIndex();

    analysisManager->FillNtupleDColumn(0, 0, pos[0]);
    analysisManager->FillNtupleDColumn(0, 1, pos[1]);
    analysisManager->FillNtupleDColumn(0, 2, pos[2]);
    analysisManager->FillNtupleIColumn(0, 3, particleType);
    analysisManager->AddNtupleRow(0);
  }

  // Process events in the big BPM hit collection.
  screenHC = GetHitsCollection(fBpmHCID, anEvent);
  for (int i=0; i<screenHC->entries(); ++i) {
    MyScreenHit* screenHit = (*screenHC)[i];

    pos = screenHit->GetPos();
    particleType = screenHit->GetParticleTypeIndex();

    analysisManager->FillNtupleDColumn(1, 0, pos[0]);
    analysisManager->FillNtupleDColumn(1, 1, pos[1]);
    analysisManager->FillNtupleDColumn(1, 2, pos[2]);
    analysisManager->FillNtupleIColumn(1, 3, particleType);
    analysisManager->AddNtupleRow(1);
  }
}


MyScreenHitsCollection* MyEventAction::GetHitsCollection(
  G4int hcID, const G4Event* anEvent) const
{
  MyScreenHitsCollection* hitsCollection = static_cast<MyScreenHitsCollection*>(
    anEvent->GetHCofThisEvent()->GetHC(hcID)
  );

  if (!hitsCollection) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception(
        "MyEventAction::GetHitsCollection()",
        "MyCode0001", FatalException, msg
    );
  }

  return hitsCollection;
}
