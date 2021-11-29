#pragma once

#include "PeptidePlane.h"
#include "Triangle.h"
#include "ProteinViewer/pdb/model/Chain.h"

namespace ribbon
{
	typedef TPair<TArray<FVector>, TArray<FVector>> VectorsPair;
	typedef TPair<FColor, FColor> ColorPair;

	TArray<FVector> ellipseProfile(const int n, const double width, const double height);

	TArray<FVector> rectangleProfile(const int n, const double width, const double height);

	TArray<FVector> roundedRectangleProfile(const int n, const double width, const double height);

	TArray<FVector> scaleProfile(const TArray<FVector> p, const double scale);

	TArray<FVector> translateProfile(const TArray<FVector> p, const double dx, const double dy);

	VectorsPair segmentProfiles(const PeptidePlane& pp1, const PeptidePlane& pp2, const int n);

	ColorPair segmentColors(const PeptidePlane& pp);

	void triangulateQuad(
		TArray<Triangle>& triangles,
		const FVector& p1, const FVector& p2, const FVector& p3, const FVector& p4,
		const FColor& c1, const FColor& c2, const FColor& c3, const FColor& c4
	);

	TArray<Triangle> createSegmentMesh(
		int i, const int n,
		const PeptidePlane& pp1, const PeptidePlane& pp2,
		const PeptidePlane& pp3, const PeptidePlane& pp4
	);

	TArray<Triangle> createChainMesh(const pdb::Chain& chain);
	
	TArray<TArray<Triangle>> createSecondaryStructureMesh(const pdb::Chain& chain);
}
