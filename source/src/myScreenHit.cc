#include "myScreenHit.hh"

#include <iomanip>

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"


G4Allocator<MyScreenHit>* MyScreenHitAllocator=0;


MyScreenHit::MyScreenHit()
: G4VHit(),
  fTrackID(-1),
  fPos(G4ThreeVector()),
  fParticleType()
{}


MyScreenHit::MyScreenHit(const MyScreenHit& right) : G4VHit() {
  fTrackID = right.fTrackID;
  fPos = right.fPos;
  fParticleType = right.fParticleType;
}


MyScreenHit::~MyScreenHit() {}


const MyScreenHit& MyScreenHit::operator=(const MyScreenHit& right) {
  fTrackID = right.fTrackID;
  fPos = right.fPos;
  fParticleType = right.fParticleType;

  return *this;
}


G4int MyScreenHit::operator==(const MyScreenHit& right) const {
  return (this == &right) ? 1 : 0;
}


void MyScreenHit::Draw() {
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager) {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.0);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.0, 0.0, 0.0);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}


void MyScreenHit::Print() {
  G4cout
    << "  trackID: " << fTrackID << "  "
    << fParticleType << "  "
    << std::setw(7) << G4BestUnit(fPos, "Length")
    << G4endl;
}
