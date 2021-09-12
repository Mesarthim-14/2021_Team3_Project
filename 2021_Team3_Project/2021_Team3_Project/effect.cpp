//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : oguma akira
// 更新日 : 2021/08/31
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define ANGLE_RADIAN					(D3DXToRadian((float)(rand() % 360)))	//ラジアンの角度
#define PARTICLE_TEXTURE_SOMKE			("data/Texture/Smoke.png")				//パーティクルのテクスチャ
#define PARTICLE_TEXTURE_EXPLOSION		("data/Texture/Explosion_Animation.png")//パーティクルのテクスチャ
#define PARTICLE_TEXTURE_WAVE			("data/Texture/Wave_Effect.png")		//パーティクルのテクスチャ
#define PARTICLE_TEXTURE_WOOD_EP		("data/Texture/Wood_Animation.png")		//パーティクルのテクスチャ
#define ALPHA_VALUE_DECREASE			(0.001f)								//アルファ値の減少値
#define MAX_GRAVITY_COUNTER_EXPLOSION	(30000)									//爆発の高さの最大値
#define MAX_GRAVITY_COUNTER_SPLASH		(10000)									//水しぶきの高さの最大値
#define MAX_GRAVITY_COUNTER_WAVE		(300)									//波の高さの最大値
#define PARTICLE_Fall_WAVE				(0.5f)									//降下倍率
#define MAX_TEXTURE_SIZE				(5.0f)									//テクスチャサイズの倍率最大値
#define MIN_TEXTURE_SIZE				(0.5f)									//テクスチャサイズの倍率最小値
#define ANIMETION_DEFAULT				(D3DXVECTOR2(1, 1))						//アニメーション無し
#define ANIMETION_EXPLOSION				(D3DXVECTOR2(16, 4))					//アニメーション爆発
#define ANIMETION_WOOD					(D3DXVECTOR2(8, 4))						//アニメーション木材

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9	CEffect::m_apTexture[EFFECT_TEXTURE_MAX] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CEffect::CEffect(PRIORITY Prioity) : CBillboard(Prioity)
{
	m_bLoop = false;//アニメーションループ
}

//=============================================================================
//デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
//クリエイト関数
//=============================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	CEffect *m_pEffect = NULL;	//メモリ確保

								//NULLチェック
	if (m_pEffect == NULL)
	{
		//メモリ確保
		m_pEffect = new CEffect;
		switch (type)
		{
			//煙
		case EFFECT_TYPE::EFFECT_TYPE_1:
			m_pEffect->Smoke(pos, size, move, col, type, Life);
			break;

			//爆発
		case EFFECT_TYPE::EFFECT_TYPE_2:
			m_pEffect->Explosion(pos, size, col, type, Life);
			break;

			//波
		case EFFECT_TYPE::EFFECT_TYPE_3:
			m_pEffect->Wave(pos, size, move, rot, col, type, Life);
			break;

			//水しぶき
		case EFFECT_TYPE::EFFECT_TYPE_4:
			m_pEffect->Splash(pos, size, move, col, type, Life);
			break;

			//木材
		case EFFECT_TYPE::EFFECT_TYPE_5:
			m_pEffect->WoodExplosion(pos, size, move, col, type, Life);
			break;

		default:
			break;
		}
	}
	else
	{
		//エラーのメッセージBOX
		MessageBox(NULL, TEXT("Error in effect.cpp"),
			TEXT("effect.cppNULLチェック出来ませんでした。"), MB_OK);
	}
	return m_pEffect;
}

//=============================================================================
//煙エフェクトの関数
//=============================================================================
void CEffect::Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//変数宣言
	D3DXVECTOR3 ActualMove = ZeroVector3;									//移動量
	D3DXVECTOR3 CreatePos = ZeroVector3;									//生成位置
	D3DXVECTOR3 RandomSize = ZeroVector3;									//画像のランダムサイズ
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//最大サイズ
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//最小サイズ

	//パーティクル分繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//角度計算
		float fAngle = ANGLE_RADIAN;
		//半径
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//慣性角度
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//位置
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//大きさ
		RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;	//アニメーションループ
		Init(CreatePos, RandomSize, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_1]);//テクスチャ情報を格納
	}
}

//=============================================================================
//木材エフェクトの関数
//=============================================================================
void CEffect::WoodExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//変数宣言
	D3DXVECTOR3 ActualMove = ZeroVector3;									//移動量
	D3DXVECTOR3 CreatePos = ZeroVector3;									//生成位置
	D3DXVECTOR3 RandomSize = ZeroVector3;									//画像のランダムサイズ
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//最大サイズ
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//最小サイズ

	//パーティクル分繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//角度計算
		float fAngle = ANGLE_RADIAN;
		//半径
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//慣性角度
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//位置
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//大きさ
		RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;

		Init(CreatePos, RandomSize, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_4]);//テクスチャ情報を格納
	}
}

//=============================================================================
//爆発エフェクト関数
//=============================================================================
void CEffect::Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	Init(pos, size, ZeroVector3, type, col, Life);
	BindTexture(m_apTexture[EFFECT_TEXTURE_2]);//テクスチャ情報を格納
}

//=============================================================================
//波エフェクト関数
//=============================================================================
void CEffect::Wave(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//パーティクルの移動角度
	D3DXVECTOR3 ActualMove = ZeroVector3;									//移動量
																			//D3DXVECTOR3 CreatePos = ZeroVector3;									//生成位置
																			//D3DXVECTOR3 RandomSize = ZeroVector3;									//画像のランダムサイズ
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//最大サイズ
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//最小サイズ

																									//パーティクル分繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//角度計算
		float fAngle = ANGLE_RADIAN;
		//半径
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//慣性角度
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)sin(fr + nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//大きさ
		//RandomSize.x = (MinSize.x) + (int)(rand()*(MaxSize.x - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		//RandomSize.y = (MinSize.y) + (int)(rand()*(MaxSize.y - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;//アニメーションループ
		Init(pos, size, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_3]);//テクスチャ情報を格納
	}
}

//=============================================================================
//水しぶきエフェクトの関数
//=============================================================================
void CEffect::Splash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//パーティクルの移動角度
	D3DXVECTOR3 ActualMove = ZeroVector3;									//移動量
	D3DXVECTOR3 CreatePos = ZeroVector3;									//生成位置
																			//D3DXVECTOR3 RandomSize = ZeroVector3;									//画像のランダムサイズ
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//最大サイズ
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//最小サイズ

	//パーティクル分繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//角度計算
		float fAngle = ANGLE_RADIAN;
		//半径
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//慣性角度
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//位置
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//大きさ
		//RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		//RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;//アニメーションループ
		Init(CreatePos, size, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_3]);//テクスチャ情報を格納
	}
}

//=============================================================================
//テクスチャの読み込み関数
//=============================================================================
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_SOMKE, &m_apTexture[EFFECT_TEXTURE_1]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_EXPLOSION, &m_apTexture[EFFECT_TEXTURE_2]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_WAVE, &m_apTexture[EFFECT_TEXTURE_3]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_WOOD_EP, &m_apTexture[EFFECT_TEXTURE_4]);

	return S_OK;
}

//=============================================================================
//テクスチャの破棄関数
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TEXTURE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//初期化関数
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, EFFECT_TYPE type, D3DXCOLOR col, int Life)
{
	//ビルボードの初期化
	SetMove(move);					//移動量
	GetColor() = col;
	SetLife(Life);
	m_nType = type;
	CBillboard::Init(pos, size);

	//
	switch (type)
	{
		//煙
	case EFFECT_TYPE::EFFECT_TYPE_1:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//爆発
	case EFFECT_TYPE::EFFECT_TYPE_2:
		CBillboard::InitAnimation(ANIMETION_EXPLOSION, 0);
		break;

		//波
	case EFFECT_TYPE::EFFECT_TYPE_3:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//水しぶき
	case EFFECT_TYPE::EFFECT_TYPE_4:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//木材
	case EFFECT_TYPE::EFFECT_TYPE_5:
		CBillboard::InitAnimation(ANIMETION_WOOD, m_bLoop);
		break;

	default:
		break;
	}
	return S_OK;
}

//=============================================================================
//更新関数
//=============================================================================
void CEffect::Update(void)
{
	//種類ごとの高さの設定と降下設定
	switch (m_nType)

	{
		//爆発
	case EFFECT_TYPE_1:
		if ((rand() % MAX_GRAVITY_COUNTER_EXPLOSION) < GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y*PARTICLE_Fall_WAVE, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//波
	case EFFECT_TYPE_3:
		if (MAX_GRAVITY_COUNTER_WAVE< GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//水しぶき
	case EFFECT_TYPE_4:
		if ((rand() % MAX_GRAVITY_COUNTER_SPLASH)< GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//木材
	case EFFECT_TYPE_5:
		if ((rand() % MAX_GRAVITY_COUNTER_EXPLOSION) < GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

	default:
		break;
	}
	//地面より下であれば
	if (GetPos().y < 0)
	{
		Uninit();

		return;
	}
	SetColor(D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a -= ALPHA_VALUE_DECREASE));
	CBillboard::Update();
}

//=============================================================================
//終了関数
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
//描画関数
//=============================================================================
void CEffect::Draw(void)
{
	CBillboard::Draw();
}

