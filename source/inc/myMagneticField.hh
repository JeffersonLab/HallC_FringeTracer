#ifndef myMagneticField_h
#define myMagneticField_h 1

#include "myTabField01.hh"

#include "G4MagneticField.hh"

#include "globals.hh"

#include <vector>


//! Interface class to the magnetic field.
class MyMagneticField : public G4MagneticField {
  public:
    //! A constructor.
    MyMagneticField();
    //! A destructor.
    virtual ~MyMagneticField();

    //! Gets the summed field value of all individual fields at the point.
    virtual void GetFieldValue(const G4double point[4], G4double* bField) const;

    //! Updates magnetic fields.
    void updateField();

  private:
    //! Holds all individual magnetic fields contributing to this field.
    std::vector<MyTabField> magFields;
};

#endif  // myMagneticField_h
