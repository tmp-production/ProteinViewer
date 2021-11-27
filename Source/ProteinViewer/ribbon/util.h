#pragma once

#include "Element.h"
#include "ProteinViewer/pdb/model/Atom.h"

inline FVector atomPosition(const pdb::Atom& atom)
{
	return FVector(atom.x, atom.y, atom.z);
}

inline ribbon::Element atomElement(const pdb::Atom& atom)
{
	return ribbon::elementBySymbol.at(atom.element);
}
