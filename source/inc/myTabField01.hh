#ifndef myTabField01_h
#define myTabField01_h 1

#include "myConfig.hh"

#include "G4ThreeVector.hh"

#include "globals.hh"

#include <vector>


//! A class detailing a tabulated magnetic field.
class MyTabField {
  public:
    //! A constructor.
    MyTabField(const config::MagnetConfig& magConf);
    //! A destructor.
    virtual ~MyTabField();

    //! Gets field value at the point.
    virtual void GetFieldValue(const G4double point[4], G4double* bField) const;

    //! A transformation from target cs to the field cs.
    void transform(const G4double point[4], G4double* tpoint) const;
    //! A trilinear interpolation of the field.
    G4double interpolate(
      const std::vector<G4double> &field,
      const G4int posIndex[3],
      const G4double posLocal[3]
    ) const;

  private:
    //! Translation between target and Tosca cs.
    G4ThreeVector transTosca;
    //! Rotation between target and Tosca cs.
    G4double thTosca;
    //! Cosine of the thTosca.
    G4double cth;
    //! Sine of the thTosca.
    G4double sth;

    //! Field map values for Bx.
    std::vector<G4double> xField;
    //! Field map values for By.
    std::vector<G4double> yField;
    //! Field map values for Bz.
    std::vector<G4double> zField;
    //! Grid size in x, y and z.
    G4int gridSize[3];
    //! Field boundary, min(x), min(y) and min(z).
    G4double boundaryMin[3];
    //! Field boundary, max(x), max(y) and max(z).
    G4double boundaryMax[3];

    //! Parses a Tosca field map as a plain txt file (not used).
    void parseToscaPlain(const config::MagnetConfig& magConf);
    //! Parses a Tosca field map as a xz compressed file (used).
    void parseToscaXz(const config::MagnetConfig& magConf);
};

#endif  // myTabField01_h
