#include <G4VUserActionInitialization.hh>

#include "PrimaryGeneratorAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ~ActionInitialization();
    void Build() const override;
};
