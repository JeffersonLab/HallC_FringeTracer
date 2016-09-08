#include "myTabField01.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"

#include <cmath>
#include <fstream>


MyTabField::MyTabField() {
  // Transformation from HB Tosca to target coordinate system.
  transTosca = G4ThreeVector(17.259*cm, 0.0*cm, 175.142*cm);
  thTosca = 187.0 * 3.14159265358979323846/180.0;
  cth = cos(-1.0*thTosca);
  sth = sin(-1.0*thTosca);

  std::ifstream ifs("data/HB-V9pt3-11pt3Gev.table");

  if (!ifs.is_open()) {
    G4cerr << "File could not be opened!" << G4endl;
    exit(1);
  }

  G4cout << G4endl << G4endl;
  G4cout << "Reading in HB magnetic field!" << G4endl;

  G4double x=0.0, y=0.0, z=0.0, Bx=0.0, By=0.0, Bz=0.0;

  // Read in grid size.
  ifs >> gridSize[2] >> gridSize[1] >> gridSize[0];
  int len = gridSize[0]*gridSize[1]*gridSize[2];

  xField.resize(len, 0.0);
  yField.resize(len, 0.0);
  zField.resize(len, 0.0);

  // Skip the rest of header.
  ifs.ignore(256, '0');

  // Read the grid.
  ifs >> x >> y >> z >> Bx >> By >> Bz;
  xField[0] = Bx;
  yField[0] = By;
  zField[0] = Bz;

  boundaryMin[0] = x*cm;
  boundaryMin[1] = y*cm;
  boundaryMin[2] = z*cm;

  for (int i=1; i<len; ++i) {
    ifs >> x >> y >> z >> Bx >> By >> Bz;
    xField[i] = Bx*gauss;
    yField[i] = By*gauss;
    zField[i] = Bz*gauss;
  }

  boundaryMax[0] = x*cm;
  boundaryMax[1] = y*cm;
  boundaryMax[2] = z*cm;

  G4cout << G4endl << G4endl;

  ifs.close();
}


MyTabField::~MyTabField() {}


void MyTabField::GetFieldValue(const G4double point[4], G4double* bField) const {
  //G4cout << "(" << point[0] << ", " << point[1] << ", "
  //<< point[2] << ", " << point[3] << ")" << G4endl;

  bField[0] = 0.0;
  bField[1] = 0.0;
  bField[2] = 0.0;

  G4double tpoint[4];
  transform(point, tpoint);

  G4bool yNeg = false;
  if (tpoint[1]<0.0) {
    tpoint[1] *= -1.0;
    yNeg = true;
  }

  if (
    boundaryMin[0]<=tpoint[0] && tpoint[0]<=boundaryMax[0] &&
    boundaryMin[1]<=tpoint[1] && tpoint[1]<=boundaryMax[1] &&
    boundaryMin[2]<=tpoint[2] && tpoint[2]<=boundaryMax[2]
  ) {
    G4double posFraction[3] = {0.0, 0.0, 0.0};
    G4double posLocal[3] = {0.0, 0.0, 0.0};
    G4double posIndexd[3] = {0.0, 0.0, 0.0};
    G4int posIndex[3] = {0, 0, 0};

    for (size_t i=0; i<3; ++i) {
      posFraction[i] = (tpoint[i]-boundaryMin[i]) / (boundaryMax[i]-boundaryMin[i]);
      posLocal[i] = (std::modf(posFraction[i]*(gridSize[i]-1), &posIndexd[i]));
      posIndex[i] = static_cast<G4int>(posIndexd[i]);

      if (posIndex[i]==gridSize[i]-1) {
        --posIndex[i];
        posLocal[i] = 1.0;
      }
    }

    bField[0] = interpolate(xField, posIndex, posLocal);
    bField[1] = interpolate(yField, posIndex, posLocal);
    bField[2] = interpolate(zField, posIndex, posLocal);

    if (yNeg) {
      bField[0] *= -1.0;
      bField[2] *= -1.0;
    }
  }
}


void MyTabField::transform(const G4double point[4], G4double* tpoint) const {
  double xt = point[0] - transTosca[0];
  double zt = point[2] - transTosca[2];

  tpoint[0] = cth*xt + sth*zt;
  tpoint[1] = point[1];
  tpoint[2] = cth*zt - sth*xt;
  tpoint[3] = point[3];
}


G4double MyTabField::interpolate(
  const std::vector<G4double> &field,
  const G4int posIndex[3],
  const G4double posLocal[3]
) const {
  return
    field[(posIndex[2]) + gridSize[2]*(posIndex[1]) + gridSize[2]*gridSize[1]*(posIndex[0])] * (1-posLocal[0])*(1-posLocal[1])*(1-posLocal[2]) +
    field[(posIndex[2]) + gridSize[2]*(posIndex[1]) + gridSize[2]*gridSize[1]*(posIndex[0]+1)] * (posLocal[0])*(1-posLocal[1])*(1-posLocal[2]) +
    field[(posIndex[2]) + gridSize[2]*(posIndex[1]+1) + gridSize[2]*gridSize[1]*(posIndex[0]+1)] * (posLocal[0])*(posLocal[1])*(1-posLocal[2]) +
    field[(posIndex[2]) + gridSize[2]*(posIndex[1]+1) + gridSize[2]*gridSize[1]*(posIndex[0])] * (1-posLocal[0])*(posLocal[1])*(1-posLocal[2]) +
    field[(posIndex[2]+1) + gridSize[2]*(posIndex[1]) + gridSize[2]*gridSize[1]*(posIndex[0])] * (1-posLocal[0])*(1-posLocal[1])*(posLocal[2]) +
    field[(posIndex[2]+1) + gridSize[2]*(posIndex[1]) + gridSize[2]*gridSize[1]*(posIndex[0]+1)] * (posLocal[0])*(1-posLocal[1])*(posLocal[2]) +
    field[(posIndex[2]+1) + gridSize[2]*(posIndex[1]+1) + gridSize[2]*gridSize[1]*(posIndex[0]+1)] * (posLocal[0])*(posLocal[1])*(posLocal[2]) +
    field[(posIndex[2]+1) + gridSize[2]*(posIndex[1]+1) + gridSize[2]*gridSize[1]*(posIndex[0])] * (1-posLocal[0])*(posLocal[1])*(posLocal[2]);
}
