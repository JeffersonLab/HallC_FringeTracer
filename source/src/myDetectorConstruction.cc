#include "myDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


myDetectorConstruction::myDetectorConstruction() : G4VUserDetectorConstruction() {}


myDetectorConstruction::~myDetectorConstruction() {}


G4VPhysicalVolume* myDetectorConstruction::Construct() {
  // Material manager.
  G4NistManager* nist = G4NistManager::Instance();

  // World.
  G4double world_hx = 1.0*m;
  G4double world_hy = 1.0*m;
  G4double world_hz = 3.0*m;

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

  // Screen.
  G4double screen_hx = 40.0*cm;
  G4double screen_hy = 40.0*cm;
  G4double screen_hz = 0.5*cm;

  G4Material* screenMat = nist->FindOrBuildMaterial("G4_Al");

  G4Box* screenBox = new G4Box("Screen", screen_hx, screen_hy, screen_hz);
  G4LogicalVolume* screenLog = new G4LogicalVolume(screenBox, screenMat, "Screen");
  new G4PVPlacement(
    0,  // rotation
    G4ThreeVector(0.0, 0.0, 2.0*m),  // location
    screenLog,  // logical volume
    "Screen",  // name
    worldLog,  // mother volume
    false,  // boolean operation
    0  // copy number
  );

  // Return physical world.
  return worldPhys;
}
