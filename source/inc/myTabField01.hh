#ifndef myTabField01_h
#define myTabField01_h 1

#include "G4ThreeVector.hh"

#include "globals.hh"

#include <vector>


class MyTabField {
  public:
    MyTabField();
    virtual ~MyTabField();

    virtual void GetFieldValue(const G4double point[4], G4double* bField) const;

    void transform(const G4double point[4], G4double* tpoint) const;

  private:

    G4ThreeVector transTosca;
    G4double thTosca;
    G4double cth, sth;

    std::vector<G4double> yField;
    G4int nx, ny, nz, len;
    G4double xMin, yMin, zMin;
    G4double xMax, yMax, zMax;
};

#endif  // myTabField01_h
