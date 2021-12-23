#pragma once

namespace ribbon
{
	struct Vertex
	{
		FVector position;
		FColor color;
	};

	struct Triangle
	{
		Vertex vertices[3];
	};
}
