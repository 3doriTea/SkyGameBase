#include "pch\pch.h"
#include "Debug.h"

#include "Core/Game.h"
#include "Input.h"

#include "GameSystem/Model.h"
#include "GameSystem/ShaderCompile.h"

#include "GameSystem/ModelMesh/Fbx.h"

#include "GameSystem/ModelMesh/IMeshSimple.h"

#include "GameSystem/CPMeshRenderer.h"

//#include 

#include "ResourceSystem.h"

#include "WTGBAssert.h"

size_t wtgb::Debug::componentOptInstanceCount_{};

wtgb::Debug* wtgb::Debug::pInstance_{ nullptr };

wtgb::Debug::Debug() :
	hSphere_{ INVALID_HANDLE },
	system_{ nullptr }
{
	pInstance_ = this;
}

wtgb::Debug::~Debug()
{
}

wtgb::Result wtgb::Debug::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();

	hTestPointSphere_ = _viewer.Get<Model>().Load("Models/TestSphere/TestPoint.fbx");
	hTestPointShader_ = _viewer.Get<ShaderCompile>().Compile(
		{
			.fileName = "Shader/TestPoint.hlsl",
			.vertexShader
			{
				.entryPointName = "VS",
				.compileVersion = "vs_5_0",
			},
			.pixelShader
			{
				.entryPointName = "PS",
				.compileVersion = "ps_5_0",
			},
			.vertexInputLayout
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },   // 位置
			},
			.fillMode = D3D11_FILL_SOLID,  // 塗りつぶし
			.cullMode = D3D11_CULL_BACK,   // 隠面消去しない
			.backIsClockwise = false,
		});

	hSphere_ = _viewer.Get<Model>().Load("Models/DebModel/DebugSphere.fbx");
	hShader_ = _viewer.Get<ShaderCompile>().Compile(
		{
			.fileName = "Shader/Debug.hlsl",
			.vertexShader
			{
				.entryPointName = "VS",
				.compileVersion = "vs_5_0",
			},
			.pixelShader
			{
				.entryPointName = "PS",
				.compileVersion = "ps_5_0",
			},
			.vertexInputLayout
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },   // 位置
			},
			.fillMode = D3D11_FILL_WIREFRAME,  // ワイヤーフレーム
			.cullMode = D3D11_CULL_NONE,       // 隠面消去しない
			.backIsClockwise = false,
		});
	return Result::Code::Ok;
}

void wtgb::Debug::Update(const ViewerUpdate& _system)
{
	Input::InputGetter input{ _system.Get<Input>().Getter() };
}

void wtgb::Debug::End()
{
}

wtgb::IMeshSimple* wtgb::Debug::GetDebugSphere()
{
	IMeshSimple* pMeshSimple{ System().Get<Model>().GetModel(hSphere_) };
	return pMeshSimple;
}

void wtgb::Debug::DrawPoint(const Vector3& _position)
{
	IMeshSimple* pMeshSimple{ pInstance_->System().Get<Model>().GetModel(pInstance_->hTestPointSphere_) };

	Transform transform{};
	transform.SetPosition(_position);

	pInstance_->System().Get<CPTransform>().CalculateLocalTransform(&transform);
	pInstance_->System().Get<CPTransform>().CalculateTransformRoot(&transform);

	pInstance_->System().Get<CPMeshRenderer>().Render(
		pMeshSimple,
		&transform,
		pInstance_->hTestPointShader_);
}
