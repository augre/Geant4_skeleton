/**
 *
 */

#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

class G4TessellatedSolid;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DetectorMessenger;
class G4Material;
class G4Colour;
class G4Tubs;

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
	private:
		G4VPhysicalVolume* Coll1Phys;
		DetectorMessenger* detectorMessenger;
		
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();
		
		virtual G4VPhysicalVolume* Construct();
		virtual void ConstructSDandField();
		virtual void SetInnerRadius(G4double);
};

#endif
