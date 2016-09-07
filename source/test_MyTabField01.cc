#include <cmath>
#include <iostream>

#include "G4SystemOfUnits.hh"

#include "globals.hh"

#include "myTabField01.hh"


void print_point(const G4double point[4]);

void test_transformation(
  const G4double point[4], const G4double tpoint[4], const G4double rpoint[4]
);


int main() {
  std::cout << "Testing." << std::endl;

  MyTabField magField;


  std::cout << "  Transformations:" << std::endl;

  G4double point[4], rpoint[4], tpoint[4];


  point[0] = 0.0; point[1] = 0.0; point[2] = 0.0; point[3] = 0.0;
  rpoint[0] = -42.1408651149; rpoint[1] = 0.0; rpoint[2] = 1759.39861089; rpoint[3] = 0.0;
  magField.transform(point, tpoint);
  test_transformation(point, tpoint, rpoint);

  point[0] = 1000.0; point[1] = 2000.0; point[2] = 3000.0; point[3] = 4000.0;
  rpoint[0] = -669.078986541; rpoint[1] = 2000.0; rpoint[2] = -1340.10918744; rpoint[3] = 4000.0;
  magField.transform(point, tpoint);
  test_transformation(point, tpoint, rpoint);



}


void print_point(const G4double point[4]) {
  std::cout << "(" << point[0] << ", " << point[1] << ", "
  << point[2] << ", " << point[3] << ")";
}


void test_transformation(
  const G4double point[4], const G4double tpoint[4], const G4double rpoint[4]
) {
  std::cout << std::endl << "    ";
  print_point(point);
  std::cout << " -> ";
  print_point(rpoint);
  std::cout << "  ";

  if (
    rpoint[0]-1E-6<=tpoint[0] && tpoint[0]<=rpoint[0]+1E-6 &&
    rpoint[2]-1E-6<=tpoint[2] && tpoint[2]<=rpoint[2]+1E-6
  ) std::cout << "success!" << std::endl;
  else std::cout << "failed!" << std::endl;

  std::cout << "      ";
  print_point(tpoint);
  std::cout << std::endl;
}
