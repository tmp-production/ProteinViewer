#include "PeptidePlane.h"
#include "util.h"

using namespace ribbon;

PeptidePlane::PeptidePlane(
	const pdb::Residue& r1,
	const pdb::Residue& r2,
	const pdb::Residue& r3
): residue1(&r1),
   residue2(&r2),
   residue3(&r3)
{
	FVector ca1 = atomPosition(r1.atomsByName.at("CA"));
	FVector ca2 = atomPosition(r2.atomsByName.at("CA"));
	FVector o1 = atomPosition(r1.atomsByName.at("O"));

	FVector a = ca2 - ca1;
	a.Normalize();

	FVector b = o1 - ca1;
	b.Normalize();

	FVector c = a ^ b;
	b.Normalize();

	FVector d = c ^ a;
	d.Normalize();

	position = (ca1 + ca2) / 2;
	normal = c;
	forward = a;
	side = d;
}

ResiduePair PeptidePlane::transition() const
{
	auto t1 = residue1->type;
	auto t2 = residue2->type;
	auto t3 = residue3->type;

	auto type1 = t2;
	auto type2 = t2;

	if (t2 > t1 && t2 == t3)
	{
		type1 = t1;
	}

	if (t2 > t3 && t1 == t2)
	{
		type2 = t3;
	}

	return ResiduePair(type1, type2);
}

void PeptidePlane::flip()
{
	side = -side;
	normal = -normal;
	flipped = !flipped;
}
