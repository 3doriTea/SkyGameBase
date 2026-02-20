// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

#include "CBGlobal3D.hlsli"

struct VS_OUT
{
    float4 pos : SV_POSITION;  // 頂点の位置
};

// 頂点シェーダ
VS_OUT VS(float4 pos : POSITION)
{
    // ピクセルシェーダに渡す情報
    VS_OUT outData;
    
    outData.pos = mul(pos, matrixWVP);
    
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    return diffuseColor;
}
