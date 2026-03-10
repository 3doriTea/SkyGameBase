#include "pch\pch.h"
#include "Shader.h"

wtgb::Shader::Shader(const std::string& _fileName) :
	accessor_{ this },
	fileName_{ _fileName }
{
}

wtgb::Shader::~Shader()
{
}

void wtgb::Shader::Init()
{
}

void wtgb::Shader::Release()
{
	// 明示的に解放

	pVertexShader_.Reset();
	pPixelShader_.Reset();
	pVertexLayout_.Reset();
	pRasterizerState_.Reset();
}
