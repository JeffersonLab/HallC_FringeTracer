#ifndef myPrimaryGeneratorAction_h
#define myPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"


class G4Event;
class G4ParticleGun;


class myPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    myPrimaryGeneratorAction();
    virtual ~myPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* fParticleGun;
};

#endif  // myPrimaryGeneratorAction_h
