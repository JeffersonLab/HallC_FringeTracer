#ifndef myMagneticField_h
#define myMagneticField_h 1

#include "myTabField01.hh"

#include "G4MagneticField.hh"

#include "globals.hh"

#include <vector>


class MyMagneticField : public G4MagneticField {
  public:
    MyMagneticField();
    virtual ~MyMagneticField();

    virtual void GetFieldValue(const G4double point[4], G4double* bField) const;

  private:
    std::vector<MyTabField> magFields;
};

#endif  // myMagneticField_h
