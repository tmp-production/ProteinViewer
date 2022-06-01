#include "Ribbon.h"
#include "Spline.h"
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
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

ColorPair ribbon::segmentColors(const PeptidePlane& pp)
{
	FColor color1, color2;

	const auto residuePair = pp.transition();
	const auto type1 = residuePair.Key;
	const auto type2 = residuePair.Value;

	switch (type1)
	{
	case pdb::ResidueTypeHelix:
		{
			color1 = FColor::FromHex("FFB733");
			break;
		}
	case pdb::ResidueTypeStrand:
		{
			color1 = FColor::FromHex("F57336");
			break;
		}
	default:
		{
			color1 = FColor::FromHex("047878");
			break;
		}
	}
	switch (type2)
	{
	case pdb::ResidueTypeHelix:
		{
			color2 = FColor::FromHex("FFB733");
			break;
		}
	case pdb::ResidueTypeStrand:
		{
			color2 = FColor::FromHex("F57336");
			break;
		}
	default:
		{
			color2 = FColor::FromHex("047878");
			break;
		}
	}

	if (type1 == pdb::ResidueTypeStrand)
	{
		color2 = color1;
	}

	return ColorPair(color1, color2);
}

void ribbon::triangulateQuad(
	TArray<Triangle>& triangles,
	const FVector& p1, const FVector& p2, const FVector& p3, const FVector& p4,
	const FColor& c1, const FColor& c2, const FColor& c3, const FColor& c4
)
{
	Triangle t1 = {
		{
			{p1, c1},
			{p2, c2},
			{p3, c3}
		}
	};

	Triangle t2 = {
		{
			{p1, c1},
			{p3, c3},
			{p4, c4}
		}
	};

	triangles.Push(t1);
	triangles.Push(t2);
}

TArray<Triangle> ribbon::createSegmentMesh(
	int i, const int n,
	const PeptidePlane& pp1, const PeptidePlane& pp2,
	const PeptidePlane& pp3, const PeptidePlane& pp4
)
{
	TArray<Triangle> triangles;

	constexpr int splineSteps = 32;
	constexpr int profileDetail = 16;

	const auto type0 = pp2.residue1->type;
	const auto residuePair = pp2.transition();
	const auto type1 = residuePair.Key;
	const auto type2 = residuePair.Value;

	const auto colorPair = segmentColors(pp2);
	const auto c1 = colorPair.Key;
	const auto c2 = colorPair.Value;

	const auto profiles = segmentProfiles(pp2, pp3, profileDetail);
	auto profile1 = profiles.Key;
	auto profile2 = profiles.Value;

	std::function<double(double)> easeFunc;
	easeFunc = [](double t)
	{
		// ease.Linear
		return t;
	};

	if (!(type1 == pdb::ResidueTypeStrand && type2 != pdb::ResidueTypeStrand))
	{
		easeFunc = [](double t)
		{
			// ease.InOutQuad
			if (t < 0.5)
			{
				return 2 * t * t;
			}

			t = 2 * t - 1;
			return -0.5 * (t * (t - 2) - 1);
		};
	}
	if (type0 == pdb::ResidueTypeStrand && type1 != pdb::ResidueTypeStrand)
	{
		easeFunc = [](double t)
		{
			// ease.OutCirc;
			t -= 1;
			return sqrt(1 - (t * t));
		};
	}

	if (i == 0)
	{
		profile1 = ellipseProfile(profileDetail, 0, 0);
		easeFunc = [](double t)
		{
			// ease.OutCirc;
			t -= 1;
			return sqrt(1 - (t * t));
		};
	}
	else if (i == n - 1)
	{
		profile2 = ellipseProfile(profileDetail, 0, 0);
		easeFunc = [](double t)
		{
			// ease.InCirc
			return -1 * (sqrt(1 - t * t) - 1);
		};
	}

	TArray<TArray<FVector>> splines1;
	splines1.Init(TArray<FVector>(), profile1.Num());

	TArray<TArray<FVector>> splines2;
	splines2.Init(TArray<FVector>(), profile2.Num());

	for (i = 0; i < splines1.Num(); i++)
	{
		const FVector p1 = profile1[i];
		const FVector p2 = profile2[i];
		splines1[i] = splineForPlanes(pp1, pp2, pp3, pp4, splineSteps, p1.X, p1.Y);
		splines2[i] = splineForPlanes(pp1, pp2, pp3, pp4, splineSteps, p2.X, p2.Y);
	}

	for (i = 0; i < splineSteps; i++)
	{
		const auto t0 = easeFunc(static_cast<double>(i) / splineSteps);
		const auto t1 = easeFunc(static_cast<double>(i + 1) / splineSteps);

		if (i == 0 && type1 == pdb::ResidueTypeStrand && type2 != pdb::ResidueTypeStrand)
		{
			const FVector p00 = splines1[0][i];
			const FVector p10 = splines1[profileDetail / 4][i];
			const FVector p11 = splines1[2 * profileDetail / 4][i];
			const FVector p01 = splines1[3 * profileDetail / 4][i];
			triangulateQuad(triangles, p00, p01, p11, p10, c1, c1, c1, c1);
		}

		for (int j = 0; j < profileDetail; j++)
		{
			const FVector p100 = splines1[j][i];
			const FVector p101 = splines1[j][i + 1];
			const FVector p110 = splines1[(j + 1) % profileDetail][i];
			const FVector p111 = splines1[(j + 1) % profileDetail][i + 1];
			const FVector p200 = splines2[j][i];
			const FVector p201 = splines2[j][i + 1];
			const FVector p210 = splines2[(j + 1) % profileDetail][i];
			const FVector p211 = splines2[(j + 1) % profileDetail][i + 1];
			const FVector p00 = FMath::Lerp(p100, p200, t0);
			const FVector p01 = FMath::Lerp(p101, p201, t1);
			const FVector p10 = FMath::Lerp(p110, p210, t0);
			const FVector p11 = FMath::Lerp(p111, p211, t1);
			const FColor c00 = FMath::Lerp(FLinearColor(c1), FLinearColor(c2), t0).ToFColor(false);
			const FColor c01 = FMath::Lerp(FLinearColor(c1), FLinearColor(c2), t1).ToFColor(false);
			const FColor c10 = FMath::Lerp(FLinearColor(c1), FLinearColor(c2), t0).ToFColor(false);
			const FColor c11 = FMath::Lerp(FLinearColor(c1), FLinearColor(c2), t1).ToFColor(false);
			triangulateQuad(triangles, p10, p11, p01, p00, c10, c11, c01, c00);
		}
	}

	return triangles;
}

TArray<FResidue> ribbon::createResidueMeshes(const pdb::Chain& chain)
{
	TArray<FResidue> sections;
	TArray<PeptidePlane> planes;

	for (int i = 0; i + 2 < chain.residues.size(); i++)
	{
		const auto& r1 = chain.residues[i];
		const auto& r2 = chain.residues[i + 1];
		const auto& r3 = chain.residues[i + 2];

		planes.Emplace(r1, r2, r3);
	}

	FVector previous;
	for (int i = 0; i < planes.Num(); i++)
	{
		PeptidePlane p = planes[i];
		if (i > 0 && (p.side | previous) < 0)
		{
			p.flip();
		}
		previous = p.side;
	}

	const int n = planes.Num() - 3;
	for (int i = 0; i < n; i++)
	{
		const auto& pp1 = planes[i];
		const auto& pp2 = planes[i + 1];
		const auto& pp3 = planes[i + 2];
		const auto& pp4 = planes[i + 3];

		const auto mesh = createSegmentMesh(i, n, pp1, pp2, pp3, pp4);

		TArray<FVector> Vertices;
		TArray<int32> Indexes;

		for (const auto& triangle : mesh)
		{
			for (const auto& vertex : triangle.vertices)
			{
				Vertices.Add(vertex.position);
				Indexes.Add(Indexes.Num());
			}
		}

		const auto meshSection = FMeshSectionStruct(Vertices, Indexes);
		const auto residueType = static_cast<EResidueType>(planes[i+2].residue1->type);
		sections.Emplace(meshSection, residueType);
	}

	return sections;
}
