#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  fParticleGun = new G4ParticleGun();
  fParticleGun->SetParticleDefinition(G4Proton::ProtonDefinition());
  fParticleGun->SetParticleEnergy(20.*GeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -0.4*m));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
