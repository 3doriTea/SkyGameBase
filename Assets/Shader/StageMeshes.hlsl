// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

#include "MainTexture.hlsli"
#include "CBGlobal3D.hlsli"
#include "CBPlayer.hlsli"
#include "CBStage.hlsli"

struct VS_OUT
{
	float4 pos : SV_POSITION;  // 頂点の位置
	float4 worldPos : TEXCOORD1;
	float4 uv : TEXCOORD0;      // 頂点に対応するUV座標
	float4 color : COLOR;      // 色 / 明るさ
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
    float3 playerPositionRatio = Player_Position.xyz;
    playerPositionRatio.x /= Stage_UVRatioX_UVRatioY.x;
    playerPositionRatio.y = 0.0f;
    playerPositionRatio.z /= Stage_UVRatioX_UVRatioY.y;
	
    //return float4(playerPositionRatio, 1.0f);
	
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	
    //return float4(playerPositionRatio, 1.0f);
	
	
    float2 pixWorldPositionRatio = float2(inData.worldPos.x, inData.worldPos.z / Stage_UVRatioX_UVRatioY.y);
	
    //return float4(worldPosition, 0.0f, 1.0f);
	
    //dcolor.y /= Stage_UVRatioX_UVRatioY.y;
	
    //return float4(dcolor, 1.0f);
	
    if (playerPositionRatio.x < pixWorldPositionRatio.x)
	{
		return float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	float4 diffuse;

	if (hasTexture)
	{
		diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
	}
	else
	{
		diffuse = diffuseColor;
	}
	
	{
	#if 0
	float4 light = float4(0, -1, 0, 0); //normalize(lightDirection);
	
	//float4 normalColor = saturate(dot(inData.normal, -light));
	float4 color = diffuse * (1.0f - inData.color) * 1.0f + diffuse * ambientValue * 0.5f;
	//color.rgb += (0.5 - length(color.rgb)) * float3(0, 0, 1);
	//float4 color = inData.color;
	float grade = 1.0f - saturate(dot(inData.normal, float4(0, 0, 1, 0)));
	//color.rgb += float3(0.7, 0.7, 0.7) * grade;
	//color.rgb += float3(1.0, 0.7, 0.7) * grade;
	color.rgb += float3(0.7, 1.0, 0.7) * grade;
	
	#else
	float4 light = float4(0, -1, 0, 0); //normalize(lightDirection);
	
	//float4 normalColor = saturate(dot(inData.normal, -light));
	float4 color = diffuse * inData.color * 1.0f + diffuse * ambientValue * 0.5f;
	//color.rgb += (0.5 - length(color.rgb)) * float3(0, 0, 1);
	//float4 color = inData.color;
	float grade = saturate(dot(inData.normal, float4(0, 0, 1, 0)));
	//color.rgb += float3(0.7, 0.7, 0.7) * grade;
	//color.rgb += float3(1.0, 0.7, 0.7) * grade;
	color.rgb += float3(0.7, 1.0, 0.7) * grade;
	#endif
		return color;
	}
	
}
