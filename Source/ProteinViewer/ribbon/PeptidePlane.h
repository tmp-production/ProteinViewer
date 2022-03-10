#pragma once
#include "ProteinViewer/parsers/pdb/model/Residue.h"

namespace ribbon
{
	typedef TPair<pdb::ResidueType, pdb::ResidueType> ResiduePair;

	struct PeptidePlane
	{
		const pdb::Residue* residue1;
		const pdb::Residue* residue2;
		const pdb::Residue* residue3;
		FVector position;
		FVector normal;
		FVector forward;
		FVector side;
		bool flipped = false;

		PeptidePlane(
			const pdb::Residue& r1,
			const pdb::Residue& r2,
			const pdb::Residue& r3
		);

		ResiduePair transition() const;

		void flip();
	};
}
