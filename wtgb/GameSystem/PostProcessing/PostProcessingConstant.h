#pragma once
#include "pch/pch.h"


namespace wtgb
{
	/// <summary>
	/// ポストプロセシングのコンスタントバッファ
	/// </summary>
	struct alignas(16) PostProcessingConstant
	{
		DirectX::XMFLOAT4 timeStrength;
	};
}
