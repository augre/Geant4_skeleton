#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction*);
    virtual ~DetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction* Detector;
    G4UIdirectory*             SkeletontronDir;
    G4UIcmdWithADouble*        SetCubeSizeCmd;
    G4UIcmdWithoutParameter*   CreateNewCubeCmd;
};


#endif

