#include "myTabField01.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"

#include <cmath>
#include <fstream>


MyTabField::MyTabField() {
  transTosca = G4ThreeVector(17.259*cm, 0.0*cm, 175.142*cm);
  thTosca = 187.0 * 3.14159265358979323846/180.0;
  cth = cos(-1.0*thTosca);
  sth = sin(-1.0*thTosca);

  std::ifstream ifs("data/HB-V9pt3-11pt3Gev.table");

  if (!ifs.is_open()) {
    G4cerr << "File could not be opened!" << G4endl;
    exit(1);
  }

  G4cout << G4endl << G4endl << G4endl << G4endl;
  G4cout << "Reading in magnetic field!" << G4endl;

  G4double x=0.0, y=0.0, z=0.0, Bx=0.0, By=0.0, Bz=0.0;
  xMin=0.0, yMin=0.0, zMin=0.0;
  xMax=0.0, yMax=0.0, zMax=0.0;

  // Read in grid size.
  ifs >> nz >> ny >> nx;
  len = nx*ny*nz;
  //G4cout << nx << " " << ny << " " << nz << " " << len << G4endl;

  yField.resize(len, 0.0);

  // Skip the rest of header.
  ifs.ignore(256, '0');

  // Read the grid.
  ifs >> x >> y >> z >> Bx >> By >> Bz;
  xMin = x*cm; yMin = y*cm; zMin = z*cm;
  yField[0] = By;
  //G4cout << "x: " << x << "  y: " << y << "  z: " << z << G4endl;
  //G4cout << "Bx: " << Bx << "  By: " << By << "  Bz: " << Bz << G4endl;
  for (int i=1; i<len; ++i) {
    ifs >> x >> y >> z >> Bx >> By >> Bz;
    yField[i] = By*gauss;
  }
  xMax = x*cm; yMax = y*cm; zMax = z*cm;

  G4cout << xMin << " < x < " << xMax << G4endl;
  G4cout << yMin << " < y < " << yMax << G4endl;
  G4cout << zMin << " < z < " << zMax << G4endl;

  //G4cout << "x: " << x << "  y: " << y << "  z: " << z << G4endl;
  //G4cout << "Bx: " << Bx << "  By: " << By << "  Bz: " << Bz << G4endl;
  G4cout << G4endl << G4endl << G4endl << G4endl;

  ifs.close();
}


MyTabField::~MyTabField() {}


void MyTabField::GetFieldValue(const G4double point[4], G4double* bField) const {
  G4cout << "(" << point[0] << ", " << point[1] << ", "
  << point[2] << ", " << point[3] << ")" << G4endl;

  bField[0] = 0.0;
  bField[1] = 0.0;
  bField[2] = 0.0;

  G4double tpoint[4];
  transform(point, tpoint);

  if (
    xMin<=tpoint[0] && tpoint[0]<=xMax &&
    yMin<=tpoint[1] && tpoint[1]<=yMax &&
    zMin<=tpoint[2] && tpoint[2]<=zMax
  ) {
    double xFraction=0.0, yFraction=0.0, zFraction=0.0;
    xFraction = (tpoint[0] - xMin)/(xMax - xMin);
    yFraction = (tpoint[1] - yMin)/(yMax - yMin);
    zFraction = (tpoint[2] - zMin)/(zMax - zMin);

    double xdi=0.0, ydi=0.0, zdi=0.0;
    double xLocal = (std::modf(xFraction*(nx-1), &xdi));
    double yLocal = (std::modf(yFraction*(ny-1), &ydi));
    double zLocal = (std::modf(zFraction*(nz-1), &zdi));
    int xi = static_cast<int>(xdi);
    int yi = static_cast<int>(ydi);
    int zi = static_cast<int>(zdi);

    if (xi==nx-1) {--xi; xLocal = 1.0;}
    if (yi==ny-1) {--yi; yLocal = 1.0;}
    if (zi==nz-1) {--zi; zLocal = 1.0;}

    bField[1] =
      yField[(zi)+nz*(yi)+nz*ny*(xi)] * (1-xLocal)*(1-yLocal)*(1-zLocal) +
      yField[(zi)+nz*(yi)+nz*ny*(xi+1)] * (xLocal)*(1-yLocal)*(1-zLocal) +
      yField[(zi)+nz*(yi+1)+nz*ny*(xi+1)] * (xLocal)*(yLocal)*(1-zLocal) +
      yField[(zi)+nz*(yi+1)+nz*ny*(xi)] * (1-xLocal)*(yLocal)*(1-zLocal) +
      yField[(zi+1)+nz*(yi)+nz*ny*(xi)] * (1-xLocal)*(1-yLocal)*(zLocal) +
      yField[(zi+1)+nz*(yi)+nz*ny*(xi+1)] * (xLocal)*(1-yLocal)*(zLocal) +
      yField[(zi+1)+nz*(yi+1)+nz*ny*(xi+1)] * (xLocal)*(yLocal)*(zLocal) +
      yField[(zi+1)+nz*(yi+1)+nz*ny*(xi)] * (1-xLocal)*(yLocal)*(zLocal);

    bField[1] *= gauss;


    //bField[1] = 1*tesla;
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
