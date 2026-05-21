/**
* 2D描画時の共通のコンスタントバッファ
*/
cbuffer Global2D : register(b0)
{
    float4x4 matrixProj;  // プロジェクションの合成行列
    float4x4 matrixUV;    // UV変換行列
    float4 color;         // 塗りつぶす色
    float alpha;          // 透明度
};

struct VS_OUT
{
    float4 pos : SV_POSITION;  // 頂点の位置
    float4 uv : TEXCOORD;      // 頂点に対応するUV座標
};
