#include "myMagneticField.hh"

#include "globals.hh"


MyMagneticField::MyMagneticField() : G4MagneticField(), magField() {}


MyMagneticField::~MyMagneticField() {}


void MyMagneticField::GetFieldValue(const G4double point[4], G4double* bField) const {
  magField.GetFieldValue(point, bField);
}
