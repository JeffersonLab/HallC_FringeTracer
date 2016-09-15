#ifndef myScreenHit_h
#define myScreenHit_h 1

#include "G4Allocator.hh"
#include "G4String.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

#include "globals.hh"


//! Class detailing a hit on the screen.
class MyScreenHit : public G4VHit {
  public:
    //! A constructor.
    MyScreenHit();
    //! A copy constructor.
    MyScreenHit(const MyScreenHit&);
    //! A destructor.
    virtual ~MyScreenHit();

    //! Assignment operator.
    const MyScreenHit& operator=(const MyScreenHit&);
    //! Equality operator.
    G4int operator==(const MyScreenHit&) const;
    //! New operator.
    inline void* operator new(size_t);
    //! Delete operator.
    inline void operator delete(void*);

    //! Draws the hit in the visualization.
    virtual void Draw();
    //! Prints the hit to the output.
    virtual void Print();

    //! Sets track ID.
    void SetTrackID(G4int track) {fTrackID = track;};
    //! Sets position of the hit.
    void SetPos(G4ThreeVector xyz) {fPos = xyz;};
    //! Sets particle type.
    void SetParticleType(G4String type) {fParticleType = type;};
    //! Sets detector copy number.
    void SetCopyNo(G4int no) {fCopyNo = no;};

    //! Gets track ID.
    G4int GetTrackID() const {return fTrackID;};
    //! Gets position of the hit.
    G4ThreeVector GetPos() const {return fPos;};
    //! Gets particle type.
    G4String GetParticleType() const {return fParticleType;};
    //! Gets index of particle type.
    G4int GetParticleTypeIndex() const;
    //! Gets detector copy number.
    G4int GetCopyNo() {return fCopyNo;};

  private:
    //! Track ID.
    G4int fTrackID;
    //! Position of the hit.
    G4ThreeVector fPos;
    //! Particle type.
    G4String fParticleType;
    //! Detector copy number.
    G4int fCopyNo;
};


//! Typedef of a screen hits collection.
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
