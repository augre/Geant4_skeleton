#include "DetectorMessenger.h"
#include "DetectorConstruction.h"                     
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* Det):Detector(Det)
{
	SkeletontronDir = new G4UIdirectory("/skeleton/");
	SkeletontronDir->SetGuidance("UI commands to use DetectorConstruction methods.");

	SetInnerRadiusCmd = new G4UIcmdWithADouble("/skeleton/SetInnerRadius",this);
	SetInnerRadiusCmd->SetGuidance("Set the inner radius of the tube.");
  
}

DetectorMessenger::~DetectorMessenger()
{
	delete SkeletontronDir;
	delete SetInnerRadiusCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
	if( command == SetInnerRadiusCmd ) {
		Detector->SetInnerRadius(SetInnerRadiusCmd->GetNewDoubleValue(newValue));
	}
}
