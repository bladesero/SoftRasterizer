#include "objloader.h"



objloader::objloader()
{
}


objloader::~objloader()
{
}

bool objloader::loadobj(const char * path, MeshData &mesh)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
		return false;

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader,"v")==0)
		{
			MrVector vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.f;
			Tmp_vertex.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			MRFLOAT2 uv;
			fscanf(file, "%f %f\n", &uv.u, &uv.v);
			Tmp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			MrVector normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal.w = 0.f;
			Tmp_vertex.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file,
				"%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches!=9)
			{
				return false;
			}
			mesh.VertexIndices.push_back(vertexIndex[0]);
			mesh.VertexIndices.push_back(vertexIndex[1]);
			mesh.VertexIndices.push_back(vertexIndex[2]);
			mesh.UVIndices.push_back(uvIndex[0]);
			mesh.UVIndices.push_back(uvIndex[1]);
			mesh.UVIndices.push_back(uvIndex[2]);
			mesh.NormalIndices.push_back(normalIndex[0]);
			mesh.NormalIndices.push_back(normalIndex[1]);
			mesh.NormalIndices.push_back(normalIndex[2]);
		}
		else
		{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	VertexIn vIn;

	for (unsigned int i = 0; i < mesh.VertexIndices.size(); i++)
	{
		//unsigned int vertexIndex = VertexIndices[i];
		//unsigned int uvIndex = UVIndices[i];
		//unsigned int normalIndex = NormalIndices[i];

		//MrVector vertex = Tmp_vertex[vertexIndex - 1];
		//MRFLOAT2 uv = Tmp_uvs[uvIndex - 1];
		//MrVector normal = Tmp_normals[normalIndex - 1];

		vIn.pos = Tmp_vertex[i];
		vIn.tex = Tmp_uvs[i];
		vIn.normal = Tmp_normals[i];
		mesh.vertices.push_back(vIn);
	}
}
