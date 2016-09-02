#include "myPrimaryGeneratorAction.hh"

#include "globals.hh"
#include "Randomize.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"


MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  // Construct particle gun that shoots numberOfParticles at a time.
  G4int numberOfParticles = 1;
  fParticleGun = new G4ParticleGun(numberOfParticles);

  // Set particle kinematic.
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
  fParticleGun->SetParticleEnergy(6.0*GeV);
}


MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() {
  delete fParticleGun;
}


void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  G4double x0 = 8.0*mm * (G4UniformRand()-0.5);
  G4double y0 = 8.0*mm * (G4UniformRand()-0.5);

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, -30.0*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
