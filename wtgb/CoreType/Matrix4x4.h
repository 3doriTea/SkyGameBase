#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// 4x4 çsóÒ
	/// </summary>
	struct Matrix4x4 : DirectX::XMMATRIX
	{
		Matrix4x4() :
			XMMATRIX{ DirectX::XMMatrixIdentity() }
		{}

		Matrix4x4(const Vector4& _l0, const Vector4& _l1, const Vector4& _l2, const Vector4& _l3) :
			XMMATRIX{ _l0, _l1, _l2, _l3 }
		{}
		Matrix4x4(const Matrix4x4& _other) = default;
		Matrix4x4(const DirectX::XMMATRIX& _xmMatrix) :
			XMMATRIX{ _xmMatrix }
		{}

		Matrix4x4& operator=(const Matrix4x4& _other)
		{
			if (this != &_other)
			{
				XMMATRIX::operator=(_other);
			}
			return *this;
		}
	};
}
