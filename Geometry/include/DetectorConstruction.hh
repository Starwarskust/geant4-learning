#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>

#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Element.hh>

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4PVReplica.hh>

#include <G4UserLimits.hh>
#include <G4VisAttributes.hh>

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();
    G4VPhysicalVolume* Construct() override;
};
