#pragma once
#include "PeptidePlane.h"

namespace ribbon
{
	TArray<FVector> spline(
		const FVector& v1, const FVector& v2,
		const FVector& v3, const FVector& v4,
		const int n
	);

	TArray<FVector> splineForPlanes(
		const PeptidePlane& p1, const PeptidePlane& p2,
		const PeptidePlane& p3, const PeptidePlane& p4,
		const int n, const double u, const double v
	);
}
