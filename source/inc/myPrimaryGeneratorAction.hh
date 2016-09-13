#ifndef myPrimaryGeneratorAction_h
#define myPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"


class G4Event;
class G4ParticleGun;


//! A class detailing the primary particle generator.
class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    //! A constructor.
    MyPrimaryGeneratorAction();
    //! A destructor.
    virtual ~MyPrimaryGeneratorAction();

    //! Generates primary particles for an event.
    virtual void GeneratePrimaries(G4Event*);

  private:
    //! Pointer to particle gun.
    G4ParticleGun* fParticleGun;
};

#endif  // myPrimaryGeneratorAction_h
