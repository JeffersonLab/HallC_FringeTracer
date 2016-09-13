#ifndef myPhysicsList_h
#define myPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


//! A class detailing the physics used in the simulation.
class MyPhysicsList : public G4VModularPhysicsList {
  public:
    //! A constructor.
    MyPhysicsList();
    //! A destructor.
    virtual ~MyPhysicsList();

    //! Sets physics cuts.
    virtual void SetCuts();
};

#endif  // myPhysicsList_h
