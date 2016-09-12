#include "myRunAction.hh"
#include "myConfig.hh"

#include "myAnalysis.hh"

#include "G4Run.hh"


MyRunAction::MyRunAction() : G4UserRunAction() {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->CreateNtuple("screen_hits", "screen hits");
  analysisManager->CreateNtupleDColumn("x [mm]");
  analysisManager->CreateNtupleDColumn("y [mm]");
  analysisManager->CreateNtupleDColumn("z [mm]");
  analysisManager->CreateNtupleIColumn("particle type");
  analysisManager->FinishNtuple();
}


MyRunAction::~MyRunAction() {}


void MyRunAction::BeginOfRunAction(const G4Run*) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile(config::screenHitOutName);
}


void MyRunAction::EndOfRunAction(const G4Run*) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();
}
