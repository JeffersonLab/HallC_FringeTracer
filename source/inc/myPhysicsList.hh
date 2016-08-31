#ifndef myPhysicsList_h
#define myPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class MyPhysicsList : public G4VModularPhysicsList {
  public:
    MyPhysicsList();
    virtual ~MyPhysicsList();

    virtual void SetCuts();
};

#endif  // myPhysicsList_h
