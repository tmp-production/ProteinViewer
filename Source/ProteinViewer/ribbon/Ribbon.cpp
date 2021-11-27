#include "Ribbon.h"

using namespace ribbon;

TArray<FVector> ribbon::ellipseProfile(const int n, const double width, const double height)
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

TArray<FVector> ribbon::rectangleProfile(const int n, const double width, const double height)
{
	TArray<FVector> result;
	result.Reserve(n);

	const double hw = width / 2;
	const double hh = height / 2;

	FVector segments[4][2] = {
		{FVector(hw, hh, 0), FVector(-hw, hh, 0)},
		{FVector(-hw, hh, 0), FVector(-hw, -hh, 0)},
		{FVector(-hw, -hh, 0), FVector(hw, -hh, 0)},
		{FVector(hw, -hh, 0), FVector(hw, hh, 0)}
	};

	const int m = n / 4;

	for (int i = 0; i < 4; i++)
	{
		const FVector* segment = segments[i];
		for (int j = 0; j < m; j++)
		{
			const double t = static_cast<double>(j) / static_cast<double>(m);
			result.Push(FMath::Lerp(segment[0], segment[1], t));
		}
	}

	return result;
}

TArray<FVector> ribbon::roundedRectangleProfile(const int n, const double width, const double height)
{
	TArray<FVector> result;
	result.Reserve(n);

	const double r = height / 2;
	const double hw = width / 2 - r;
	const double hh = height / 2;

	FVector segments[4][2] = {
		{FVector(hw, hh, 0), FVector(-hw, hh, 0)},
		{FVector(-hw, 0, 0), FVector(0)},
		{FVector(-hw, -hh, 0), FVector(hw, -hh, 0)},
		{FVector(hw, 0, 0), FVector(0)}
	};


	const int m = n / 4;

	for (int i = 0; i < 4; i++)
	{
		const FVector* segment = segments[i];
		for (int j = 0; j < m; j++)
		{
			const double t = static_cast<double>(j) / static_cast<double>(m);
			FVector p;

			switch (i)
			{
			case 0:
			case 2:
				{
					p = FMath::Lerp(segment[0], segment[1], t);
					break;
				}
			case 1:
				{
					const double a = M_PI / 2 + M_PI * t;
					const double x = cos(a) * r;
					const double y = sin(a) * r;
					p = segment[0] + FVector(x, y, 0);
					break;
				}
			case 3:
				{
					const double a = 3 * M_PI / 2 + M_PI * t;
					const double x = cos(a) * r;
					const double y = sin(a) * r;
					p = segment[0] + FVector(x, y, 0);
					break;
				}
			default: break;
			}

			result.Push(p);
		}
	}

	return result;
}

TArray<FVector> ribbon::scaleProfile(const TArray<FVector> p, const double scale)
{
	auto pCopy = TArray<FVector>(p);
	for (FVector& vector : pCopy)
	{
		vector *= scale;
	}
	return pCopy;
}

TArray<FVector> ribbon::translateProfile(const TArray<FVector> p, const double dx, const double dy)
{
	auto pCopy = TArray<FVector>(p);
	for (FVector& vector : pCopy)
	{
		vector += FVector(dx, dy, 0);
	}
	return pCopy;
}

VectorsPair ribbon::segmentProfiles(const PeptidePlane& pp1, const PeptidePlane& pp2, const int n)
{
	TArray<FVector> profile1, profile2;

	const auto type0 = pp1.residue1->type;
	const auto residuePair = pp1.transition();
	const auto type1 = residuePair.Key;
	const auto type2 = residuePair.Value;

	constexpr double ribbonWidth = 2;
	constexpr double ribbonHeight = 0.125;
	constexpr double ribbonOffset = 1.5;
	constexpr double arrowHeadWidth = 3;
	constexpr double arrowWidth = 2;
	constexpr double arrowHeight = 0.5;
	constexpr double tubeSize = 0.75;

	double offset1 = ribbonOffset;
	double offset2 = ribbonOffset;

	if (pp1.flipped)
	{
		offset1 = -offset1;
	}

	if (pp2.flipped)
	{
		offset2 = -offset2;
	}

	switch (type1)
	{
	case pdb::ResidueTypeHelix:
		{
			if (type0 == pdb::ResidueTypeStrand)
			{
				profile1 = roundedRectangleProfile(n, 0, 0);
			}
			else
			{
				profile1 = roundedRectangleProfile(n, ribbonWidth, ribbonHeight);
			}
			profile1 = translateProfile(profile1, 0, offset1);
			break;
		}
	case (pdb::ResidueTypeStrand):
		{
			if (type2 == pdb::ResidueTypeStrand)
			{
				profile1 = rectangleProfile(n, arrowWidth, arrowHeight);
			}
			else
			{
				profile1 = rectangleProfile(n, arrowHeadWidth, arrowHeight);
			}
			break;
		}
	default:
		{
			if (type0 == pdb::ResidueTypeStrand)
			{
				profile1 = ellipseProfile(n, 0, 0);
			}
			else
			{
				profile1 = ellipseProfile(n, tubeSize, tubeSize);
			}
			break;
		}
	}

	switch (type2)
	{
	case pdb::ResidueTypeHelix:
		{
			profile2 = roundedRectangleProfile(n, ribbonWidth, ribbonHeight);
			profile2 = translateProfile(profile2, 0, offset2);
			break;
		}
	case (pdb::ResidueTypeStrand):
		{
			profile2 = rectangleProfile(n, arrowWidth, arrowHeight);
			break;
		}
	default:
		{
			profile2 = ellipseProfile(n, tubeSize, tubeSize);
			break;
		}
	}

	if (type1 == pdb::ResidueTypeStrand && type2 != pdb::ResidueTypeStrand)
	{
		profile2 = rectangleProfile(n, 0, arrowHeight);
	}

	return VectorsPair(profile1, profile2);
}
