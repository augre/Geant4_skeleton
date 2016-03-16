#include "DetectorConstruction.h"

//Material manager
#include "G4NistManager.hh"
//Basic Units.
#include "G4SystemOfUnits.hh"

//Basic Volume and Placement
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

//Types of Volumes
#include "G4Box.hh"

//Include necessary scorers
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"


#include "G4Colour.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction() :
	G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

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
	G4double world_sizeXY = 5*cm;
	G4double world_sizeZ  = 30*cm;

	G4Box* solidWorld =    
		new G4Box("World",                       //its name
				0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);    //its size

	G4LogicalVolume* logicWorld =                         
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
	G4double innerRadius = 3.25*mm;
	G4double outerRadius = 6*mm;
	G4double hz = 39.5*mm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;


	G4Tubs* Coll1
	  = new G4Tubs("Primary_collimator",
	      innerRadius, 
	      outerRadius,
	      hz,
	      startAngle, 
	      spanningAngle);
	G4LogicalVolume* Coll1Log
	  = new G4LogicalVolume(Coll1, W95, "Primary_collimator");
	Coll1Log->SetVisAttributes(red_solid);



	G4RotationMatrix *rotation=new G4RotationMatrix();
	G4VPhysicalVolume* Coll1Phys = new G4PVPlacement(rotation,G4ThreeVector(),Coll1Log,"Tube",logicWorld,false,0,checkOverlaps);

	//Return the world
	return physWorld;
}

/**In this routine we construct the Senditive Detector (SD). This is where the scorers are registered.
 */
void DetectorConstruction::ConstructSDandField() 
{
}
