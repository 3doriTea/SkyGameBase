#include "pch\pch.h"
#include "Fbx.h"

wtgb::Fbx::Fbx()
{
}

wtgb::Fbx::~Fbx()
{
}

HRESULT wtgb::Fbx::TryLoad(const std::string& _fileName)
{
	ufbx_load_opts options{};
	ufbx_error error{};

	ufbx_scene* pScene{ ufbx_load_file(_fileName.data(), &options, &error) };
	if (pScene == nullptr)
	{
		return S_FALSE;
	}

	for (ufbx_node* pNode : pScene->nodes)
	{
	}

	ufbx_free_scene(pScene);




	return S_OK;
}

void wtgb::Fbx::Draw(Transform& transform)
{
	
}

void wtgb::Fbx::Release()
{
}

void wtgb::Fbx::InitVertex(ufbx_mesh* pMesh, ufbx_mesh_part* pPart)
{
	std::vector<Vertex> vertexes{};
	std::vector<uint32_t> triangleIndices{};
	triangleIndices.resize(pMesh->max_face_triangles * 3);

	for (uint32_t faceIndex : pPart->face_indices)
	{
		ufbx_face face{ pMesh->faces[faceIndex] };

		uint32_t numberTriangles
		{
			ufbx_triangulate_face(
				triangleIndices.data(),
				triangleIndices.size(),
				pMesh,
				face)
		};

		for (size_t i = 0; i < numberTriangles * 3; i++)
		{
			uint32_t index{ triangleIndices[i] };

			Vertex vertex{};
			vertex.position =
			{
				static_cast<float>(pMesh->vertex_position[index].x),
				static_cast<float>(pMesh->vertex_position[index].y),
				static_cast<float>(pMesh->vertex_position[index].z),
			};
			vertex.normal =
			{
				static_cast<float>(pMesh->vertex_normal[index].x),
				static_cast<float>(pMesh->vertex_normal[index].y),
				static_cast<float>(pMesh->vertex_normal[index].z),
			};
			vertex.uv =
			{
				static_cast<float>(pMesh->vertex_uv[index].x),
				static_cast<float>(pMesh->vertex_uv[index].y),
			};
			vertexes.push_back(vertex);
		}


	}
}
