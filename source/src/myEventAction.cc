#include "myEventAction.hh"

#include "myAnalysis.hh"
#include "myScreenHit.hh"

#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"


MyEventAction::MyEventAction() : G4UserEventAction(), fScreenHCID(-1) {}


MyEventAction::~MyEventAction() {}


void MyEventAction::BeginOfEventAction(const G4Event*) {}


void MyEventAction::EndOfEventAction(const G4Event* anEvent) {
  // Assing ID at the first event of the run.
  if (fScreenHCID == -1) {
    fScreenHCID = G4SDManager::GetSDMpointer()->GetCollectionID("screenHitsCollection");
  }

  MyScreenHitsCollection* screenHC = GetHitsCollection(fScreenHCID, anEvent);
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Process events in the hits collection.
  for (int i=0; i<screenHC->entries(); ++i) {
    MyScreenHit* screenHit = (*screenHC)[i];

    G4ThreeVector pos = screenHit->GetPos();
    G4String particleType = screenHit->GetParticleType();

    analysisManager->FillNtupleDColumn(0, pos[0]);
    analysisManager->FillNtupleDColumn(1, pos[1]);
    analysisManager->FillNtupleDColumn(2, pos[2]);
    // Fill type of particle.
    if (particleType=="e-") analysisManager->FillNtupleIColumn(3, 0);
    else if (particleType=="e+") analysisManager->FillNtupleIColumn(3, 1);
    else if (particleType=="gamma") analysisManager->FillNtupleIColumn(3, 2);
    else analysisManager->FillNtupleIColumn(3, -1);

    analysisManager->AddNtupleRow();
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
