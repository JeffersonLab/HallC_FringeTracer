#ifndef myPhysicsList_h
#define myPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class myPhysicsList : public G4VModularPhysicsList {
  public:
    myPhysicsList();
    virtual ~myPhysicsList();

    virtual void SetCuts();
};

#endif  // myPhysicsList_h
