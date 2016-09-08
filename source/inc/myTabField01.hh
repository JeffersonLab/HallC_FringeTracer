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
    G4double interpolate(
      const std::vector<G4double> &field,
      const G4int posIndex[3],
      const G4double posLocal[3]
    ) const;

  private:
    G4ThreeVector transTosca;
    G4double thTosca;
    G4double cth, sth;

    std::vector<G4double> xField;
    std::vector<G4double> yField;
    std::vector<G4double> zField;
    G4int gridSize[3];
    G4double boundaryMin[3];
    G4double boundaryMax[3];
};

#endif  // myTabField01_h
