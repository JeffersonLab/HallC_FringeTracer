#include "myDetectorConstruction.hh"
#include "myConfig.hh"
#include "myMagneticField.hh"
#include "myMessenger.hh"
#include "myScreenSD.hh"

#include "G4Box.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4AutoDelete.hh"
#include "G4TransportationManager.hh"
#include "G4UserLimits.hh"

#include "G4ios.hh"


// Initialization of static members.
MyMagneticField* MyDetectorConstruction::fMagneticField = 0;
G4FieldManager* MyDetectorConstruction::fFieldMgr = 0;
MySHMSmessenger* MyDetectorConstruction::fSHMSmessenger = 0;


MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction() {}


MyDetectorConstruction::~MyDetectorConstruction() {}


G4VPhysicalVolume* MyDetectorConstruction::Construct() {
  // Material manager.
  G4NistManager* nist = G4NistManager::Instance();

  // World.
  G4double hx = 1.0*m;
  G4double hy = 1.0*m;
  G4double hz = 52.0*m;

  G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* worldBox = new G4Box("World", hx, hy, hz);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, worldMat, "World");

  G4VPhysicalVolume* worldPhys = new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 0.0),  // location
    worldLog,  // logical volume
    "World",  // name
    0,  // mother volume
    false,  // boolean operation
    0  // copy number
  );

  // Set step limit in world.
  G4UserLimits* userLimits = new G4UserLimits(10*cm);
  worldLog->SetUserLimits(userLimits);

  // Target.
  // 1.5% radiation length carbon
  G4Material* targetMat = nist->FindOrBuildMaterial("G4_C");
  G4double radLength_C = 42.7 * g/cm/cm;

  hx = 10.0*cm;
  hy = 10.0*cm;
  hz = 0.015*radLength_C/targetMat->GetDensity() / 2.0;

  G4Box* targetBox = new G4Box("Target_C", hx, hy, hz);
  G4LogicalVolume* targetLog = new G4LogicalVolume(targetBox, targetMat, "Target_C");
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 0.0),  // location
    targetLog,  // logical volume
    "Target_C",  // name
    worldLog,  // mother volume
    false,  // boolean operation
    0  // copy number
  );

  // Gun frame.
  G4Material* gunMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* gunBox = new G4Box("Gun", 2.0*cm, 2.0*cm, 10*cm);
  G4LogicalVolume* gunLog = new G4LogicalVolume(gunBox, gunMat, "Gun");
  new G4PVPlacement(
    0,
    G4ThreeVector(0.0, 0.0, -40.0*cm),
    gunLog,
    "Gun",
    worldLog,
    false,
    0
  );

  // Beam dump screen.
  hx = 40.0*cm;
  hy = 40.0*cm;
  hz = 0.5*mm;

  G4Material* bdScreenMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* bdScreenBox = new G4Box("bdScreen", hx, hy, hz);
  G4LogicalVolume* bdScreenLog = new G4LogicalVolume(bdScreenBox, bdScreenMat, "bdScreen");
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 51.8*m),  // location
    bdScreenLog,  // logical volume
    "bdScreen",  // name
    worldLog,  // mother volume
    false,  // boolean operation
    0  // copy number
  );

  // Big BPM screen.
  hx = 30.0*cm;
  hy = 30.0*cm;
  hz = 0.5*mm;

  G4Material* bpmScreenMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* bpmScreenBox = new G4Box("bpmScreen", hx, hy, hz);
  G4LogicalVolume* bpmScreenLog = new G4LogicalVolume(bpmScreenBox, bpmScreenMat, "bpmScreen");
  // BPM 1
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 827.248*2.54*cm),  // location
    bpmScreenLog,  // logical volume
    "bpmScreen",  // name
    worldLog,  // mother volume
    false,  // boolean operation
    0  // copy number
  );
  // BPM 2
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 1010.848*2.54*cm),  // location
    bpmScreenLog,  // logical volume
    "bpmScreen",  // name
    worldLog,  // mother volume
    false,  // boolean operation
    1  // copy number
  );

  // Return physical world.
  return worldPhys;
}


void MyDetectorConstruction::ConstructSDandField() {
  // Set beam dump screen sensitive detector.
  G4String bdScreenSDname = "beam/bdScreenSD";
  MyScreenSD* bdScreenSD = new MyScreenSD(bdScreenSDname, "bdScreenHC");
  SetSensitiveDetector("bdScreen", bdScreenSD);

  G4String bpmScreenSDname = "beam/bpmScreenSD";
  MyScreenSD* bpmScreenSD = new MyScreenSD(bpmScreenSDname, "bpmScreenHC");
  SetSensitiveDetector("bpmScreen", bpmScreenSD, true);

  // Set magnetic field.
  fMagneticField = new MyMagneticField();
  fFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  fFieldMgr->SetDetectorField(fMagneticField);
  fFieldMgr->CreateChordFinder(fMagneticField);

  // Set SHMS messenger.
  fSHMSmessenger = new MySHMSmessenger(fMagneticField);

  G4AutoDelete::Register(fMagneticField);
  G4AutoDelete::Register(fFieldMgr);
  G4AutoDelete::Register(fSHMSmessenger);
}
