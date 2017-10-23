#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include "Vertex.h"
class objloader
{
public:
	std::vector<char> path;

	std::vector<MrVector> Tmp_vertex;
	std::vector<MRFLOAT2> Tmp_uvs;
	std::vector<MrVector> Tmp_normals;

	struct MeshData
	{
		std::vector<VertexIn> vertices;
		std::vector<uint32_t> VertexIndices, UVIndices, NormalIndices;
	};

	objloader();
	~objloader();

	bool loadobj(const char* path,MeshData &mesh);
};

