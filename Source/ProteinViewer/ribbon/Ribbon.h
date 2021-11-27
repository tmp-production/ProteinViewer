#pragma once
#include "PeptidePlane.h"

namespace ribbon
{
	typedef TPair<TArray<FVector>, TArray<FVector>> VectorsPair;

	TArray<FVector> ellipseProfile(const int n, const double width, const double height);

	TArray<FVector> rectangleProfile(const int n, const double width, const double height);

	TArray<FVector> roundedRectangleProfile(const int n, const double width, const double height);

	TArray<FVector> scaleProfile(const TArray<FVector> p, const double scale);

	TArray<FVector> translateProfile(const TArray<FVector> p, const double dx, const double dy);

	VectorsPair segmentProfiles(const PeptidePlane& pp1, const PeptidePlane& pp2, const int n);
}
