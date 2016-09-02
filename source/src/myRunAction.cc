#include "myRunAction.hh"

#include "myAnalysis.hh"

#include "G4Run.hh"


MyRunAction::MyRunAction() : G4UserRunAction() {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->CreateNtuple("tmp", "screen hits");
  analysisManager->CreateNtupleDColumn("x [mm]");
  analysisManager->CreateNtupleDColumn("y [mm]");
  analysisManager->CreateNtupleDColumn("z [mm]");
  analysisManager->FinishNtuple();
}


MyRunAction::~MyRunAction() {}


void MyRunAction::BeginOfRunAction(const G4Run*) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile("tmp_out");
}


void MyRunAction::EndOfRunAction(const G4Run*) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();
}
