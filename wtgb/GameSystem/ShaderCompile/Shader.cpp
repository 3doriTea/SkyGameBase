#include "pch\pch.h"
#include "Shader.h"

wtgb::Shader::Shader()
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
	// –¾Ž¦“I‚É‰ð•ú

	pVertexShader_.Reset();
	pPixelShader_.Reset();
	pVertexLayout_.Reset();
	pRasterizerState_.Reset();
}
