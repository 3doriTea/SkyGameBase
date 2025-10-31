#include "pch\pch.h"
#include "Fbx.h"

wtgb::Fbx::Fbx()
{
}

wtgb::Fbx::~Fbx()
{
}

HRESULT wtgb::Fbx::Load(const std::string& _fileName)
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
