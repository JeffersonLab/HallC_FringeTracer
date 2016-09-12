#ifndef myScreenHit_h
#define myScreenHit_h 1

#include "G4Allocator.hh"
#include "G4String.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

#include "globals.hh"


class MyScreenHit : public G4VHit {
  public:
    MyScreenHit();
    MyScreenHit(const MyScreenHit&);
    virtual ~MyScreenHit();

    const MyScreenHit& operator=(const MyScreenHit&);
    G4int operator==(const MyScreenHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

    void SetTrackID(G4int track) {fTrackID = track;};
    void SetPos(G4ThreeVector xyz) {fPos = xyz;};
    void SetParticleType(G4String type) {fParticleType = type;};

    G4int GetTrackID() const {return fTrackID;};
    G4ThreeVector GetPos() const {return fPos;};
    G4String GetParticleType() const {return fParticleType;};

  private:
    G4int fTrackID;
    G4ThreeVector fPos;
    G4String fParticleType;
};


typedef G4THitsCollection<MyScreenHit> MyScreenHitsCollection;

extern G4Allocator<MyScreenHit>* MyScreenHitAllocator;


inline void* MyScreenHit::operator new(size_t) {
  if (!MyScreenHitAllocator) MyScreenHitAllocator = new G4Allocator<MyScreenHit>;
  return (void*) MyScreenHitAllocator->MallocSingle();
}


inline void MyScreenHit::operator delete(void* aHit) {
  MyScreenHitAllocator->FreeSingle((MyScreenHit*) aHit);
}

#endif  // myScreenHit_h
