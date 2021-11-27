#include "Ribbon.h"

using namespace ribbon;

TArray<FVector> ellipseProfile(const int n, const double width, const double height)
{
	TArray<FVector> result;
	result.Init(FVector(0), n);

	for (int i = 0; i < result.Num(); i++)
	{
		const double t = static_cast<double>(i) / static_cast<double>(n);
		const double a = t * 2 * M_PI + M_PI / 4;

		result[i].X = cos(a) * width / 2;
		result[i].Y = sin(a) * height / 2;
	}

	return result;
}

TArray<FVector> rectangleProfile(const int n, const double width, const double height)
{
	TArray<FVector> result;
	result.Reserve(n);

	const double hw = width / 2;
	const double hh = height / 2;

	FVector segments[][2] = {
		{FVector(hw, hh, 0), FVector(-hw, hh, 0)},
		{FVector(-hw, hh, 0), FVector(-hw, -hh, 0)},
		{FVector(-hw, -hh, 0), FVector(hw, -hh, 0)},
		{FVector(hw, -hh, 0), FVector(hw, hh, 0)}
	};

	const int m = n / 4;

	for (const auto& segment : segments)
	{
		for (int i = 0; i < m; i++)
		{
			const double t = static_cast<double>(i) / static_cast<double>(m);
			result.Push(FMath::Lerp(segment[0], segment[1], t));
		}
	}

	return result;
}
