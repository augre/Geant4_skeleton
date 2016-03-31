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

extern "C" {
#include "LinkedList.h"
}

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
	private:
		DetectorMessenger* detectorMessenger;
		
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();
		
		virtual G4VPhysicalVolume* Construct();
		virtual void ConstructSDandField();
		virtual void SetInnerRadius(G4double);
	protected:
		List lista;
		ListElmnt *element;
		G4VPhysicalVolume *data;
};

#endif
