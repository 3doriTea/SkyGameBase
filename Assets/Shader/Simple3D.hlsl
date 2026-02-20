// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

#include "MainTexture.hlsli"
#include "CBGlobal3D.hlsli"

struct VS_OUT
{
    float4 pos : SV_POSITION;  // 頂点の位置
    float4 uv : TEXCOORD;      // 頂点に対応するUV座標
    float4 color : COLOR;      // 色 / 明るさ
};

// 頂点シェーダ
VS_OUT VS(
    float4 pos : POSITION,
    float4 normal : NORMAL,
    float4 uv : TEXCOORD)
{
    // ピクセルシェーダに渡す情報
    VS_OUT outData;
    
    outData.pos = mul(pos, matrixWVP);
    outData.uv = mul(uv, matrixUV);
    
    float4 light = normalize(lightDirection);
    
    normal = mul(normal, matrixRotateWorld);
    normal.w = 0;
    
    outData.color = saturate(dot(normal, light));
    
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    float4 diffuse;

    if (hasTexture)
    {
        diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
    }
    else
    {
        diffuse = diffuseColor;
    }
    float4 color = diffuse * inData.color + diffuse * ambientValue;
    
    return color;
}
