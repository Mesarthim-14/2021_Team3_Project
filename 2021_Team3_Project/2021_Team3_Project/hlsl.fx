//=====================================================================
// 
// シェーダ [hlsl.fx]
// Author : Konishi Yuuto
// 
//=====================================================================
//=====================================================================
// グローバル変数
//=====================================================================
// 変換マトリクス
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
float4x4 WorldViewProjectionPlayer;

// 時間関数// テクスチャ
texture NoiseTex < string type = "VOLUME"; string name = "NoiseVolume.dds"; >;
// 環境マップ
texture skyBoxTex < string type = "CUBE"; string name = "LobbyCube.dds"; >;
// カメラポジション
float4 CameraPos : CameraPosition;
// 時間関数
float Time : TIME;

texture Tex;
sampler Sampler = sampler_state 
{
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// サブセットごとに入れ替わる
float4 MaterialAmbientIntensity = { 0.01f, 0.01f, 0.01f, 1.0f }; // ambient
float4 MaterialDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };    // diffuse
float4 MaterialSpecularColor = { 0.2f, 0.2f, 0.2f, 1.0f };    // specular
float  MaterialSpecularPower = 32;                            // power
float4 MaterialEmissive;        // Emissive

//=====================================================================
// Water
//=====================================================================
sampler Noise = sampler_state
{
	Texture = (NoiseTex);
	ADDRESSU = WRAP;
	ADDRESSV = WRAP;
	ADDRESSW = WRAP;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
	MIPFILTER = LINEAR;
};

//=====================================================================
// パンプマップテクスチャ宣言
//=====================================================================
texture TexNormal;
sampler SamplerNormal = sampler_state
{
	Texture = TexNormal;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//=====================================================================
// Ocean
//=====================================================================
float waveSpeed = 0.0700;
float Ocean_noiseSpeed = 0.0700;
float waveSpeedPlayer = 0.1500;
float Ocean_noiseSpeedPlayer = 0.1500;

float fadeExp = 6.080000;										// 色の広がり
float fadeBias = 0.3000;										// 黒い部分
float3 scale = { 0.00009, 0.00009, 0.00009};
float4 waterColor = { 1.0, 1.0, 1.0, 1.0 };	// ベースの色

//--------------------------------------------------------------//
// Water
//--------------------------------------------------------------//
samplerCUBE skyBox = sampler_state
{
	Texture = (skyBoxTex);
	ADDRESSU = CLAMP;
	ADDRESSV = CLAMP;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//=====================================================================
// 頂点シェーダからピクセルシェーダに渡すデータ
//=====================================================================
struct Ocean_VS_OUTPUT
{
	float4 Pos: POSITION;
	float3 pos: TEXCOORD0;
	float3 normal: TEXCOORD1;
	float3 vVec: TEXCOORD2;
	float3 posPlayer: TEXCOORD3;
	float3 vVecPlayer: TEXCOORD4;
};

//=====================================================================
// 頂点シェーダ
//=====================================================================
Ocean_VS_OUTPUT Ocean_vs_main(float4 Pos: POSITION, float3 normal: NORMAL)
{
	Ocean_VS_OUTPUT Out;

	// マトリクスはトランスポーズする
	Out.Pos = (float4)mul(Pos, WorldViewProjection);

	// 水面を出力
	Out.pos = Pos.xyz * scale;

	// ビュー・ベクトルと法線の出力
	Out.vVec = (float3)(Pos - CameraPos);
	Out.normal = normal;

	Out.Pos = (float4)mul(Pos, WorldViewProjectionPlayer);

	// 水面を出力
	Out.posPlayer = Pos.xyz * scale;

	// ビュー・ベクトルと法線の出力
	Out.vVecPlayer = (float3)(Pos - CameraPos);

	return Out;
}

//=====================================================================
// 水面揺るがす処理
//=====================================================================
float4 Ocean_ps_main(
	float3 pos: TEXCOORD0, float3 normal: TEXCOORD1, float3 vVec: TEXCOORD2,
	float3 posPlayer: TEXCOORD3, float3 vVecPlayer: TEXCOORD4) : COLOR
{
	// 位置を揺るがせる
	pos.x += waveSpeed * Time;
	pos.z += Ocean_noiseSpeed * Time;
	
	// ボリュームテクスチャ
	float4 noisy = tex3D(Noise, pos);

	// ノイズの負の成分を無くする
	float3 bump = (float3)(2 * noisy - 0);
	bump.xz *= 1.0;

	// 法線の方向を生成
	bump.y = 0.1 * abs(bump.y) + 0.0;

	// 法線サーフェス
	bump = normalize(normal + bump);
	
	float3 reflVec = reflect(vVec, bump);			// 反射ベクトルを計算
	
	float4 refl = texCUBE(skyBox, reflVec);		// キューブテクスチャの反映

	float lrp = 1 - dot(-normalize(vVec), bump);	// 色を分ける

	float4 num = (float4)(1 - bump.y + refl)*waterColor;

	// 水面の色と反射の設定
	//return lerp(waterColor, refl, saturate(fadeBias + pow(lrp, fadeExp)));

	posPlayer.x += waveSpeedPlayer * Time;
	posPlayer.z += Ocean_noiseSpeedPlayer * Time;

	noisy = tex3D(Noise, posPlayer);

	bump = (float3)(2 * noisy - 0);

	// 法線サーフェス
	bump = normalize(normal + bump);

	reflVec = reflect(vVecPlayer, bump);			// 反射ベクトルを計算
	refl = texCUBE(skyBox, reflVec.xyz);			// キューブテクスチャの反映

	lrp = 1 - dot(-normalize(vVecPlayer), bump);	// 色を分ける

	float4 numPlayer = (float4)(1 - bump.y + refl)*waterColor;

	float4 add = num * numPlayer*0.5;
	add.a = 1.0f;

	return add;
}

//=====================================================================
// テクニック
//=====================================================================
technique Ocean
{
	pass Water
	{
		ZENABLE = TRUE;
		CULLMODE = NONE;
		ZWRITEENABLE = TRUE;
		VertexShader = compile vs_3_0 Ocean_vs_main();	
		PixelShader = compile ps_2_0 Ocean_ps_main();
	}
}
