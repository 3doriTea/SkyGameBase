// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

#include "MainTexture.hlsli"
#include "CBGlobal3D.hlsli"
#include "CBPlayer.hlsli"
#include "CBStage.hlsli"

struct VS_OUT
{
	float4 pos : SV_POSITION;     // 頂点の位置
	float4 worldPos : TEXCOORD1;  // ワールド座標
	float4 uv : TEXCOORD0;        // 頂点に対応するUV座標
	float4 color : COLOR;         // 色 / 明るさ
	float4 normal : NORMAL;
};

// 頂点シェーダ
VS_OUT VS(
	float4 pos : POSITION,
	float4 normal : NORMAL,
	float4 uv : TEXCOORD)
{
	// ピクセルシェーダに渡す情報
	VS_OUT outData;
	
    outData.worldPos = mul(pos, matrixW);
	outData.pos = mul(pos, matrixWVP);
	outData.uv = mul(uv, matrixUV);
	
	outData.normal = normal;
	
	float4 light = normalize(lightDirection);
	
	normal = mul(normal, matrixRotateWorld);
	normal.w = 0;
	
	outData.color = saturate(dot(normal, -light));
	
	return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	
    float2 playerPositionRatio = Player_Position.xz;
    playerPositionRatio.x /= Stage_UVRatioX_UVRatioY.x;
    playerPositionRatio.y /= Stage_UVRatioX_UVRatioY.y;
	
    float2 pixWorldPositionRatio = float2(inData.worldPos.x, inData.worldPos.z / Stage_UVRatioX_UVRatioY.y);
	
    float2 playerPositionPix = Player_Position.xz;
    float2 worldPositionPix = float2(
		pixWorldPositionRatio.x * Stage_UVRatioX_UVRatioY.x,
		pixWorldPositionRatio.y * Stage_UVRatioX_UVRatioY.y);
	

    float distance =
		sqrt(
			pow(playerPositionPix.x - worldPositionPix.x, 2.0f)
			+ pow(playerPositionPix.y - worldPositionPix.y, 2.0f)
		);
	
	if (hasTexture)
	{
		diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
	}
	else
	{
		diffuse = diffuseColor;
	}
	
    const float DropShadow_Radius = 3.0f;
	
    if (distance < DropShadow_Radius)
    {
        diffuse.xyz -= float3(1.0f, 1.0f, 1.0f) * (((DropShadow_Radius - distance) / DropShadow_Radius));
    }
	
	float4 light = float4(0, -1, 0, 0);
	
	float4 color = diffuse * inData.color * 1.0f + diffuse * ambientValue * 0.5f;
	float grade = saturate(dot(inData.normal, float4(0, 0, 1, 0)));
	color.rgb += float3(0.7, 1.0, 0.7) * grade;
	
	return color;
}
