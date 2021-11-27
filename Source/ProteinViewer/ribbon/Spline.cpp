#include "Spline.h"

TArray<FVector> ribbon::spline(
	const FVector& v1, const FVector& v2,
	const FVector& v3, const FVector& v4,
	const int n
)
{
	const double n1 = n;
	const double n2 = n * n;
	const double n3 = n * n * n;

	const auto s = FMatrix(
		FPlane(6 / n3, 0, 0, 0),
		FPlane(6 / n3, 2 / n2, 0, 0),
		FPlane(1 / n3, 1 / n2, 1 / n1, 0),
		FPlane(0, 0, 0, 1)
	);

	const auto b = FMatrix(
		FPlane(-1, 3, -3, 1),
		FPlane(3, -6, 3, 0),
		FPlane(-3, 0, 3, 0),
		FPlane(1, 4, 1, 0)
	) * (1.0 / 6.0);

	const auto g = FMatrix(
		FPlane(v1.X, v1.Y, v1.Z, 1),
		FPlane(v2.X, v2.Y, v2.Z, 1),
		FPlane(v3.X, v3.Y, v3.Z, 1),
		FPlane(v4.X, v4.Y, v4.Z, 1)
	);

	TArray<FVector> result;
	result.Reserve(n + 1);

	FMatrix matrix = s * b * g;
	FVector vector = FVector(
		matrix.M[3][0] / matrix.M[3][3],
		matrix.M[3][1] / matrix.M[3][3],
		matrix.M[3][2] / matrix.M[3][3]
	);

	// vector.RoundPlaces(10);
	result.Push(vector);

	for (int k = 0; k < n; k++)
	{
		matrix.M[3][0] = matrix.M[3][0] + matrix.M[2][0];
		matrix.M[3][1] = matrix.M[3][1] + matrix.M[2][1];
		matrix.M[3][2] = matrix.M[3][2] + matrix.M[2][2];
		matrix.M[3][3] = matrix.M[3][3] + matrix.M[2][3];
		matrix.M[2][0] = matrix.M[2][0] + matrix.M[1][0];
		matrix.M[2][1] = matrix.M[2][1] + matrix.M[1][1];
		matrix.M[2][2] = matrix.M[2][2] + matrix.M[1][2];
		matrix.M[2][3] = matrix.M[2][3] + matrix.M[1][3];
		matrix.M[1][0] = matrix.M[1][0] + matrix.M[0][0];
		matrix.M[1][1] = matrix.M[1][1] + matrix.M[0][1];
		matrix.M[1][2] = matrix.M[1][2] + matrix.M[0][2];
		matrix.M[1][3] = matrix.M[1][3] + matrix.M[0][3];

		vector = FVector(
			matrix.M[3][0] / matrix.M[3][3],
			matrix.M[3][1] / matrix.M[3][3],
			matrix.M[3][2] / matrix.M[3][3]
		);

		// vector.RoundPlaces(10);
		result.Push(vector);
	}

	return result;
}

TArray<FVector> ribbon::splineForPlanes(
	const PeptidePlane& p1, const PeptidePlane& p2,
	const PeptidePlane& p3, const PeptidePlane& p4,
	const int n, const double u, const double v
)
{
	const FVector g1 = p1.position + (p1.side * u) + (p1.normal * v);
	const FVector g2 = p2.position + (p2.side * u) + (p2.normal * v);
	const FVector g3 = p3.position + (p3.side * u) + (p3.normal * v);
	const FVector g4 = p4.position + (p4.side * u) + (p4.normal * v);
	return spline(g1, g2, g3, g4, n);
}
