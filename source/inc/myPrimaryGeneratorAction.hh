#ifndef myPrimaryGeneratorAction_h
#define myPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"


class G4Event;
class G4ParticleGun;


class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    MyPrimaryGeneratorAction();
    virtual ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* fParticleGun;
};

#endif  // myPrimaryGeneratorAction_h
