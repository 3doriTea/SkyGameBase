// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

#include "MainTexture.hlsli"
#include "CBGlobal3D.hlsli"

struct VS_OUT
{
    float4 pos : SV_POSITION;  // 頂点の位置
    float4 uv : TEXCOORD;      // 頂点に対応するUV座標
    float4 color : COLOR;      // 色 / 明るさ
};

VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float4 uv : TEXCOORD)
{
    VS_OUT outData;
    
    // ビュー行列の平行移動部分を消してカメラと同じ位置にする
    float4x4 viewNoTranslation = matrixView;
    viewNoTranslation._41 = 0;
    viewNoTranslation._42 = 0;
    viewNoTranslation._43 = 0;
    
    // 回転だけ適用する
    float4 worldPos = mul(pos, matrixRotateWorld);
    
    // ビュー座標を求めてプロジェクション座標に変換する
    float4 viewPos = mul(float4(worldPos.xyz, 1.0), viewNoTranslation);
    outData.pos = mul(viewPos, matrixProjection);

    // プロジェクション座標上の z / w = 1.0 -> 最背面描画にする
    outData.pos.z = outData.pos.w;
    
    outData.uv = mul(uv, matrixUV);
    outData.color = float4(1, 1, 1, 1); // ライト計算を飛ばして白くする
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    float4 diffuse;
    
    diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
    float4 color = diffuse;
    
    return color;
}
