#include "myDetectorConstruction.hh"
#include "myConfig.hh"
#include "myMagneticField.hh"
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

MyMagneticField* MyDetectorConstruction::fMagneticField = 0;
G4FieldManager* MyDetectorConstruction::fFieldMgr = 0;


MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction()
{}


MyDetectorConstruction::~MyDetectorConstruction() {}


G4VPhysicalVolume* MyDetectorConstruction::Construct() {
  // Material manager.
  G4NistManager* nist = G4NistManager::Instance();

  // World.
  G4double world_hx = 1.0*m;
  G4double world_hy = 1.0*m;
  G4double world_hz = 52.0*m;

  G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
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

  G4double target_hx = 10.0*cm;
  G4double target_hy = 10.0*cm;
  G4double target_hz = 0.015*radLength_C/targetMat->GetDensity() / 2.0;

  G4Box* targetBox = new G4Box("Target_C", target_hx, target_hy, target_hz);
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

  // Screen.
  G4double screen_hx = 40.0*cm;
  G4double screen_hy = 40.0*cm;
  G4double screen_hz = 0.5*mm;

  G4Material* screenMat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* screenBox = new G4Box("Screen", screen_hx, screen_hy, screen_hz);
  G4LogicalVolume* screenLog = new G4LogicalVolume(screenBox, screenMat, "Screen");
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 51.8*m),  // location
    screenLog,  // logical volume
    "Screen",  // name
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

  // Return physical world.
  return worldPhys;
}


void MyDetectorConstruction::ConstructSDandField() {
  // Set screen sensitive detector.
  G4String screenSDname = "beam/screenSD";
  MyScreenSD* aScreenSD = new MyScreenSD(screenSDname, "screenHitsCollection");

  SetSensitiveDetector("Screen", aScreenSD, true);

  // Set magnetic field.
  fMagneticField = new MyMagneticField();
  fFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  fFieldMgr->SetDetectorField(fMagneticField);
  fFieldMgr->CreateChordFinder(fMagneticField);

  G4AutoDelete::Register(fMagneticField);
  G4AutoDelete::Register(fFieldMgr);
}
