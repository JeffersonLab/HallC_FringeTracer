#include "myEventAction.hh"

#include "myAnalysis.hh"
#include "myScreenHit.hh"

#include "G4Event.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"


MyEventAction::MyEventAction() : G4UserEventAction(), fScreenHCID(-1) {}


MyEventAction::~MyEventAction() {}


void MyEventAction::BeginOfEventAction(const G4Event*) {}


void MyEventAction::EndOfEventAction(const G4Event* anEvent) {
  if (fScreenHCID == -1) {
    fScreenHCID = G4SDManager::GetSDMpointer()->GetCollectionID("screenHitsCollection");
  }

  MyScreenHitsCollection* screenHC = GetHitsCollection(fScreenHCID, anEvent);

  if (screenHC->entries()>0) {
    MyScreenHit* screenHit = (*screenHC)[0];

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    G4ThreeVector pos = screenHit->GetPos();

    analysisManager->FillNtupleDColumn(0, pos[0]);
    analysisManager->FillNtupleDColumn(1, pos[1]);
    analysisManager->FillNtupleDColumn(2, pos[2]);
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
