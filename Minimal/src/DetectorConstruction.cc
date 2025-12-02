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
    0,                // no rotation
    G4ThreeVector(),  // at (0, 0, 0)
    logicWorld,       // logical volume
    "World",          // name
    0,                // mother volume
    false,            // no boolean operation
    0                 // copy number
  );

  //---------------------------------------- Box ---------------------------------------------------

  G4double boxSizeXY = 0.9*m;
  G4double boxSizeZ  = 5.*cm;
  G4Box* solidBox = new G4Box("Box", boxSizeXY/2., boxSizeXY/2., boxSizeZ/2.);

  G4Material* boxMat = nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, boxMat, "Box");

  G4VPhysicalVolume* physBox = new G4PVPlacement(
    0,                // no rotation
    G4ThreeVector(),  // at (0, 0, 0)
    logicBox,         // logical volume
    "Box",            // name
    logicWorld,       // mother volume
    false,            // no boolean operation
    0                 // copy number
  );

  //--------------------------------------- Return -------------------------------------------------

  return physWorld;
}
