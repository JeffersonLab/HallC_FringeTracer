#include "myRunAction.hh"
#include "myConfig.hh"

#include "myAnalysis.hh"

#include "G4Run.hh"


MyRunAction::MyRunAction() : G4UserRunAction() {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->CreateNtuple("bdScreenHits", "beam dump screen hits");
  analysisManager->CreateNtupleDColumn(0, "x [mm]");
  analysisManager->CreateNtupleDColumn(0, "y [mm]");
  analysisManager->CreateNtupleDColumn(0, "z [mm]");
  analysisManager->CreateNtupleIColumn(0, "particle type");
  analysisManager->FinishNtuple(0);

  analysisManager->CreateNtuple("bpmScreenHits", "BPM screen hits");
  analysisManager->CreateNtupleDColumn(1, "x [mm]");
  analysisManager->CreateNtupleDColumn(1, "y [mm]");
  analysisManager->CreateNtupleDColumn(1, "z [mm]");
  analysisManager->CreateNtupleIColumn(1, "particle type");
  analysisManager->CreateNtupleIColumn(1, "BPM number");
  analysisManager->FinishNtuple(1);
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
