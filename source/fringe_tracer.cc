#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif  // G4VIS_USE
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif  // G4UI_USE

#include "myDetectorConstruction.hh"
#include "myPhysicsList.hh"
#include "myPrimaryGeneratorAction.hh"


int main(int argc, char *argv[]) {
  // Default run manager.
  G4RunManager* runManager = new G4RunManager;

  // Initialization classes.
  runManager->SetUserInitialization(new myDetectorConstruction);
  runManager->SetUserInitialization(new myPhysicsList);
  // User action classes.
  runManager->SetUserAction(new myPrimaryGeneratorAction);

  // Kernel.
  runManager->Initialize();

  // Set UI.
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif  // G4VIS_USE

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc==1) {
    // Interactive mode.
#ifdef G4UI_USE
    G4UIExecutive* UI = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#else  // G4VIS_USE
    UImanager->ApplyCommand("/control/execute init.mac");
#endif  // G4VIS_USE
    UI->SessionStart();
    delete UI;
#endif  // G4UI_USE
  }
  else {
    // Batch mode.
    G4String command = "/control/execute";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // Start run.
  int numberOfEvents = 3;
  runManager->BeamOn(numberOfEvents);

  // Terminate.
  delete visManager;
  delete runManager;
  return 0;
}
