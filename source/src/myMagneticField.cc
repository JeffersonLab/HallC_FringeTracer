#include "myMagneticField.hh"
#include "myConfig.hh"

#include "globals.hh"


MyMagneticField::MyMagneticField() : G4MagneticField() {
  // Create an entry for each field defined in the configuration file.
  for (size_t i=0; i<config::magnets.size(); ++i) {
    magFields.push_back(MyTabField(config::magnets.at(i)));
  }
}


MyMagneticField::~MyMagneticField() {}


void MyMagneticField::GetFieldValue(const G4double point[4], G4double* bField) const {
  bField[0] = 0.0;
  bField[1] = 0.0;
  bField[2] = 0.0;

  // Sum over all individual fields.
  for (size_t i=0; i<config::magnets.size(); ++i) {
    magFields.at(i).GetFieldValue(point, bField);
  }
}


void MyMagneticField::updateField() {
  for (size_t i=0; i<magFields.size(); ++i) {
    magFields.at(i).updateTransformation(config::magnets.at(i));
  }
}
