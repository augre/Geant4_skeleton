#include "DetectorConstruction.h"
#include "DetectorMessenger.h"



//Material manager
#include "G4NistManager.hh"
//Basic Units.
#include "G4SystemOfUnits.hh"

//Basic Volume and Placement
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

//Types of Volumes
#include "G4Box.hh"
#include "G4Tubs.hh"

//Include necessary scorers
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"


#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "G4RunManager.hh"

DetectorConstruction::DetectorConstruction() :
	G4VUserDetectorConstruction()
{ 
	detectorMessenger = new DetectorMessenger(this);
	LinkedList_Create(&lista, free);
}

DetectorConstruction::~DetectorConstruction()
{
	delete detectorMessenger;
	LinkedList_Destroy(&lista);
}


void DetectorConstruction::CubeSize(G4double sideLength)
{

	G4VSolid* solidDetector;
	G4Box* cube;
	G4GeometryManager::GetInstance()->OpenGeometry(data);
	solidDetector = data->GetLogicalVolume()->GetSolid();
	cube = dynamic_cast<G4Box*>(solidDetector);
	cube->SetXHalfLength(sideLength*cm);
	cube->SetYHalfLength(sideLength*cm);
	cube->SetZHalfLength(sideLength*cm);
#ifdef _DEBUG
	G4cout<<"Cube sideLength changed to "<<sideLength<<" cm"<<G4endl;
#endif
	G4GeometryManager::GetInstance()->CloseGeometry(data);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void DetectorConstruction::CreateCube()
{
	G4RotationMatrix *rotation=new G4RotationMatrix();
	if (list_size(&lista)==0)
	{
		data = new G4PVPlacement(rotation,G4ThreeVector(),CubeLog,"Cube",logicWorld,false,0,false);
		LinkedList_InsertNext(&lista, NULL, data);
	}
	else
	{
		element = list_head(&lista);
		G4ThreeVector translation;
		data=(G4VPhysicalVolume*) list_data(element);
		translation = data->GetTranslation();
		G4double xc=translation.getX();
		G4cout<<"translation "<<translation<<G4endl;
		G4cout<<"x coordinate "<<xc<<G4endl;
		data = new G4PVPlacement(rotation,G4ThreeVector(xc+600,0,0),CubeLog,"Cube",logicWorld,false,0,false);
		LinkedList_InsertNext(&lista, NULL, data);
		element = list_head(&lista);
		data=(G4VPhysicalVolume*) list_data(element);
		translation = data->GetTranslation();
		xc=translation.getX();
		G4cout<<"new cube translation "<<translation<<G4endl;
		G4cout<<"new x coordinate "<<xc<<G4endl;
	}
}

/**This routine is used to construct the geometry to be simulated. This includes the
 * necessary materials to produce objects.
 */
G4VPhysicalVolume *DetectorConstruction::Construct()
{
	// Option to switch on/off checking of volumes overlaps
	G4bool checkOverlaps = false;

	//--------------Register Materials-------------------------------//
	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* Cu	= nist->FindOrBuildMaterial("G4_Cu");
	G4Material* Fe	= nist->FindOrBuildMaterial("G4_Fe");
	G4Material* Ni	= nist->FindOrBuildMaterial("G4_Ni");
	G4Material* W 	= nist->FindOrBuildMaterial("G4_W");
	G4Material* W95 = new G4Material("W95",18.*g/cm3,4,kStateSolid);
	W95->AddMaterial(W,0.95);
	W95->AddMaterial(Cu,0.017);
	W95->AddMaterial(Ni,0.017);
	W95->AddMaterial(Fe,0.016);

	//colors

	G4VisAttributes * red_solid = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
	red_solid->SetForceSolid(true);

	// Construct the World
	G4double world_sizeXY = 1000*cm;
	G4double world_sizeZ  = 1000*cm;

	G4Box* solidWorld =    
		new G4Box("World",                       //its name
				0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);    //its size

	logicWorld =
		new G4LogicalVolume(solidWorld,          //its solid
				air,           //its material
				"World");      //its name

	G4VPhysicalVolume* physWorld = new G4PVPlacement(
			0, 					//no rotation
			G4ThreeVector(),	//at (0,0,0)
			logicWorld,			//contataing logical volume
			"World",				//name
			0,						//no mother volume
			false,				//no boolean operation
			0,						//copy number
			checkOverlaps);	//overlap checking

	//--------------Build the required geometry here-----------------//
	G4double sideL= 25.*cm;
	Cube
	  = new G4Box("Cube",
	      sideL,
	      sideL,
	      sideL);
	CubeLog
	  = new G4LogicalVolume(Cube, W95, "Primary_collimator");
	CubeLog->SetVisAttributes(red_solid);

	this->CreateCube();

	//Return the world
	return physWorld;
}

/**In this routine we construct the Senditive Detector (SD). This is where the scorers are registered.
 */
void DetectorConstruction::ConstructSDandField() 
{
}
