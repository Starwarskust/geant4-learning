#include <G4RunManager.hh>

#include "DetectorConstruction.hh"
#include <FTFP_BERT.hh>
#include "ActionInitialization.hh"

#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

int main(int argc, char* argv[])
{
  // Construct RunManager and initialize G4 kernel
  G4RunManager* runManager = new G4RunManager();
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new FTFP_BERT(0));
  runManager->SetUserInitialization(new ActionInitialization());
  runManager->Initialize();

  // Get the pointer to the VisManager and User Interface manager
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  G4UIExecutive* UI = new G4UIExecutive(argc, argv);
  UImanager->ApplyCommand("/control/execute vis.mac");
  UI->SessionStart();
  delete UI;

  // Job termination
  delete visManager;
  delete runManager;

  return 0;
}
