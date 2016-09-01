#ifndef myActionInitialization_h
#define myActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


class MyActionInitialization : public G4VUserActionInitialization {
  public:
    MyActionInitialization();
    virtual ~MyActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif  // myActionInitialization_h
