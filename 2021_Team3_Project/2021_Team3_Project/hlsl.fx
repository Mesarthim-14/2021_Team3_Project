//=====================================================================
// 
// �V�F�[�_ [hlsl.fx]
// Author : Konishi Yuuto
// 
//=====================================================================
//=====================================================================
// �O���[�o���ϐ�
//=====================================================================
// �ϊ��}�g���N�X
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
float4x4 WorldViewProjectionPlayer;

// ���Ԋ֐�// �e�N�X�`��
texture NoiseTex < string type = "VOLUME"; string name = "NoiseVolume.dds"; >;
// ���}�b�v
texture skyBoxTex < string type = "CUBE"; string name = "LobbyCube.dds"; >;
// �J�����|�W�V����
float4 CameraPos : CameraPosition;
// ���Ԋ֐�
float Time : TIME;

texture Tex;
sampler Sampler = sampler_state 
{
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// �T�u�Z�b�g���Ƃɓ���ւ��
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
// �p���v�}�b�v�e�N�X�`���錾
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

float fadeExp = 6.080000;										// �F�̍L����
float fadeBias = 0.3000;										// ��������
float3 scale = { 0.00009, 0.00009, 0.00009};
float4 waterColor = { 1.0, 1.0, 1.0, 1.0 };	// �x�[�X�̐F

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
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
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
// ���_�V�F�[�_
//=====================================================================
Ocean_VS_OUTPUT Ocean_vs_main(float4 Pos: POSITION, float3 normal: NORMAL)
{
	Ocean_VS_OUTPUT Out;

	// �}�g���N�X�̓g�����X�|�[�Y����
	Out.Pos = (float4)mul(Pos, WorldViewProjection);

	// ���ʂ��o��
	Out.pos = Pos.xyz * scale;

	// �r���[�E�x�N�g���Ɩ@���̏o��
	Out.vVec = (float3)(Pos - CameraPos);
	Out.normal = normal;

	Out.Pos = (float4)mul(Pos, WorldViewProjectionPlayer);

	// ���ʂ��o��
	Out.posPlayer = Pos.xyz * scale;

	// �r���[�E�x�N�g���Ɩ@���̏o��
	Out.vVecPlayer = (float3)(Pos - CameraPos);

	return Out;
}

//=====================================================================
// ���ʗh�邪������
//=====================================================================
float4 Ocean_ps_main(
	float3 pos: TEXCOORD0, float3 normal: TEXCOORD1, float3 vVec: TEXCOORD2,
	float3 posPlayer: TEXCOORD3, float3 vVecPlayer: TEXCOORD4) : COLOR
{
	// �ʒu��h�邪����
	pos.x += waveSpeed * Time;
	pos.z += Ocean_noiseSpeed * Time;
	
	// �{�����[���e�N�X�`��
	float4 noisy = tex3D(Noise, pos);

	// �m�C�Y�̕��̐����𖳂�����
	float3 bump = (float3)(2 * noisy - 0);
	bump.xz *= 1.0;

	// �@���̕����𐶐�
	bump.y = 0.1 * abs(bump.y) + 0.0;

	// �@���T�[�t�F�X
	bump = normalize(normal + bump);
	
	float3 reflVec = reflect(vVec, bump);			// ���˃x�N�g�����v�Z
	
	float4 refl = texCUBE(skyBox, reflVec);		// �L���[�u�e�N�X�`���̔��f

	float lrp = 1 - dot(-normalize(vVec), bump);	// �F�𕪂���

	float4 num = (float4)(1 - bump.y + refl)*waterColor;

	// ���ʂ̐F�Ɣ��˂̐ݒ�
	//return lerp(waterColor, refl, saturate(fadeBias + pow(lrp, fadeExp)));

	posPlayer.x += waveSpeedPlayer * Time;
	posPlayer.z += Ocean_noiseSpeedPlayer * Time;

	noisy = tex3D(Noise, posPlayer);

	bump = (float3)(2 * noisy - 0);

	// �@���T�[�t�F�X
	bump = normalize(normal + bump);

	reflVec = reflect(vVecPlayer, bump);			// ���˃x�N�g�����v�Z
	refl = texCUBE(skyBox, reflVec.xyz);			// �L���[�u�e�N�X�`���̔��f

	lrp = 1 - dot(-normalize(vVecPlayer), bump);	// �F�𕪂���

	float4 numPlayer = (float4)(1 - bump.y + refl)*waterColor;

	float4 add = num * numPlayer*0.5;
	add.a = 1.0f;

	return add;
}

//=====================================================================
// �e�N�j�b�N
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
