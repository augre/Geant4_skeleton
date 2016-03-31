#include "DetectorMessenger.h"
#include "DetectorConstruction.h"                     
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* Det):Detector(Det)
{
	SkeletontronDir = new G4UIdirectory("/skeleton/");
	SkeletontronDir->SetGuidance("UI commands to use DetectorConstruction methods.");

	SetCubeSizeCmd= new G4UIcmdWithADouble("/skeleton/SetCubeSizeCmd",this);
	SetCubeSizeCmd->SetGuidance("Set the length of the sides of the cube");

	CreateNewCubeCmd = new G4UIcmdWithoutParameter("/skeleton/CreateNewCubeCmd",this);
	CreateNewCubeCmd->SetGuidance("Create new cube on x axis");
}

DetectorMessenger::~DetectorMessenger()
{
	delete SkeletontronDir;
	delete SetCubeSizeCmd;
	delete CreateNewCubeCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
	if( command == SetCubeSizeCmd) {
		Detector->CubeSize(SetCubeSizeCmd->GetNewDoubleValue(newValue));
	}
	else if( command ==CreateNewCubeCmd) {
		Detector->CreateCube();
	}
}
