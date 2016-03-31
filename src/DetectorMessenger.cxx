#include "DetectorMessenger.h"
#include "DetectorConstruction.h"                     
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* Det):Detector(Det)
{
	SkeletontronDir = new G4UIdirectory("/skeleton/");
	SkeletontronDir->SetGuidance("UI commands to use DetectorConstruction methods.");

	SetCubeSizeCmd= new G4UIcmdWithADouble("/skeleton/SetCubeSizeCmd",this);
	SetCubeSizeCmd->SetGuidance("Set the length of the sides of the cube");
  
}

DetectorMessenger::~DetectorMessenger()
{
	delete SkeletontronDir;
	delete SetCubeSizeCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
	if( command == SetCubeSizeCmd) {
		Detector->CubeSize(SetCubeSizeCmd->GetNewDoubleValue(newValue));
	}
}
