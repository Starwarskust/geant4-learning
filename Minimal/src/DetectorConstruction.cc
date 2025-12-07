#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  //--------------------------------------- World --------------------------------------------------

  G4double worldSizeXY = 1.*m;
  G4double worldSizeZ  = 1.*m;
  G4Box* solidWorld = new G4Box("World", worldSizeXY/2., worldSizeXY/2., worldSizeZ/2.);

  G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(
    nullptr,          // no rotation
    G4ThreeVector(),  // at (0, 0, 0)
    logicWorld,       // logical volume
    "World",          // name
    nullptr,          // mother volume
    false,            // no boolean operation
    0                 // copy number
  );

  //--------------------------------------- Plate --------------------------------------------------

  G4double boxSizeXY = 0.9*m;
  G4double boxSizeZ  = 5.*cm;
  G4Box* solidPlate = new G4Box("Plate", boxSizeXY/2., boxSizeXY/2., boxSizeZ/2.);

  G4Material* boxMat = nist->FindOrBuildMaterial("G4_Si");
  G4LogicalVolume* logicPlate = new G4LogicalVolume(solidPlate, boxMat, "Plate");

  G4VPhysicalVolume* physPlate = new G4PVPlacement(
    nullptr,          // no rotation
    G4ThreeVector(),  // at (0, 0, 0)
    logicPlate,       // logical volume
    "Plate",          // name
    logicWorld,       // mother volume
    false,            // no boolean operation
    0                 // copy number
  );

  //--------------------------------------- Return -------------------------------------------------

  return physWorld;
}
