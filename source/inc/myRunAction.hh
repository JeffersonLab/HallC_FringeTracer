#ifndef myRunAction_h
#define myRunAction_h 1

#include "G4UserRunAction.hh"


class G4Run;


//! Class detailing actions for each run.
class MyRunAction : public G4UserRunAction {
  public:
    //! A constructor.
    MyRunAction();
    //! A destructor.
    virtual ~MyRunAction();

    //! Action ran at the beginning of the run.
    virtual void BeginOfRunAction(const G4Run*);
    //! Action ran at the end of the run.
    virtual void EndOfRunAction(const G4Run*);
};

#endif  // myRunAction_h
