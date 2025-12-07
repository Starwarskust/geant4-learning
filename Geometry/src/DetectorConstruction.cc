#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4String name;
  G4String symbol;
  G4double z;
  G4double a;
  G4double density;
  G4int nComponents;
  G4State state;
  G4double temp;
  G4int nAtoms;
  G4double fraction;

  // Define element - variant 1
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7., a=14.01*g/mole);
  // Define element - variant 2
  G4Element* elO = nist->FindOrBuildElement(z=8);

  // Define material - variant 1
  G4Material* Si = new G4Material(name="Silicium", z=14., a=28.086*g/mole, density=2.33*g/cm3);
  // Define material - variant 2
  G4Element* elH = nist->FindOrBuildElement(z=1);
  G4Material* ice = new G4Material(
    name="Ice",
    density=0.9167*g/cm3,
    nComponents=2,
    state=kStateSolid,
    temp=273.15*kelvin
  );
  ice->AddElement(elH, nAtoms=2);
  ice->AddElement(elO, nAtoms=1);
  // Define material - variant 3
  G4Material* air = new G4Material(
    name="Air",
    density=0.0012255*g/cm3,
    nComponents=2,
    state=kStateGas,
    temp=288.15*kelvin
  );
  air->AddElement(elN, fraction=0.7);
  air->AddElement(elO, fraction=0.3);

  //--------------------------------------- World --------------------------------------------------

  G4double worldSizeXY = 60.*cm;
  G4double worldSizeZ  = 60.*cm;
  G4Box* solidWorld = new G4Box("World", worldSizeXY/2., worldSizeXY/2., worldSizeZ/2.);

  G4Material* worldMat = air;
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

  G4double boxSizeXY = 50.*cm;
  G4double boxSizeZ  = 5.*cm;
  G4Box* solidPlate = new G4Box("Plate", boxSizeXY/2., boxSizeXY/2., boxSizeZ/2.);

  G4Material* boxMat = ice;
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

  //------------------------------------- Pad array ------------------------------------------------

  G4double padSizeXY = 5.*cm;
  G4double padSizeZ  = 1.*cm;
  G4Box* solidPad = new G4Box("Pad", padSizeXY/2., padSizeXY/2., padSizeZ/2.);

  G4Material* padMat = Si;
  G4LogicalVolume* logicPad = new G4LogicalVolume(solidPad, padMat, "Pad");

  //--- Variant with loop ---

  for (G4int i = 0; i < 10; i++) {
    new G4PVPlacement(
      nullptr,
      G4ThreeVector((-4.5 + i) * 5.*cm, 0., 4.*cm),
      logicPad,
      "Pad",
      logicWorld,
      false,
      i
    );
  }

  //--- Variant with G4PVReplica ---

  // G4Box* solidPadArray = new G4Box("PadArray", 10. * padSizeXY/2., padSizeXY/2., padSizeZ/2.);
  // G4LogicalVolume* logicPadArray = new G4LogicalVolume(solidPadArray, worldMat, "PadArray");
  // G4VPhysicalVolume* physPadArray = new G4PVPlacement(
  //   nullptr,
  //   G4ThreeVector(0., 0., 4.*cm),
  //   logicPadArray,
  //   "PadArray",
  //   logicWorld,
  //   false,
  //   0
  // );

  // G4VPhysicalVolume* Si_det_pvpl = new G4PVReplica(
  //   "Pad", logicPad, logicPadArray, kXAxis, 10, padSizeXY
  // );

  //------------------------------------ VisAttributes ---------------------------------------------

  G4bool visibility;
  G4Colour colour;
  G4VisAttributes* worldAttributes = new G4VisAttributes(visibility=false);
  logicWorld->SetVisAttributes(worldAttributes);
  G4VisAttributes* plateAttributes = new G4VisAttributes(colour=G4Colour::Green());
  logicPlate->SetVisAttributes(plateAttributes);
  G4VisAttributes* padAttributes = new G4VisAttributes(colour=G4Colour::Magenta());
  logicPad->SetVisAttributes(padAttributes);

  //--------------------------------------- Return -------------------------------------------------

  return physWorld;
}
