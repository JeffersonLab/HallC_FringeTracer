#ifndef myActionInitialization_h
#define myActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


//! Geant4 user action initialization class.
class MyActionInitialization : public G4VUserActionInitialization {
  public:
    //! A constructor.
    MyActionInitialization();
    //! A destructor.
    virtual ~MyActionInitialization();

    //! Sets actions for master thread.
    virtual void BuildForMaster() const;
    //! Sets actions for worker threads.
    virtual void Build() const;
};

#endif  // myActionInitialization_h
