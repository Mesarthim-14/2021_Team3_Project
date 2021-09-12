//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 小熊 朗
// 更新日 : 2022/03/04
//
//=============================================================================
#ifndef effect_H_
#define effect_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_PARTICLE (400)

//=============================================================================
//パーティクルクラス定義
//=============================================================================
class CEffect :public CBillboard
{
public:
	enum EFFECT_TYPE	//パーティクル種類
	{
		EFFECT_TYPE_NONE = -1,
		EFFECT_TYPE_1,
		EFFECT_TYPE_2,
		EFFECT_TYPE_3,
		EFFECT_TYPE_4,
		EFFECT_TYPE_5,
		EFFECT_TYPE_MAX
	};

	enum EFFECT_TEXTURE	//パーティクル画像種類
	{
		EFFECT_TEXTURE_NONE = -1,
		EFFECT_TEXTURE_1,
		EFFECT_TEXTURE_2,
		EFFECT_TEXTURE_3,
		EFFECT_TEXTURE_4,
		EFFECT_TEXTURE_MAX
	};

	CEffect();		//コンストラクタ
	~CEffect();		//デストラクタ

	//クリエイト関数
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void WoodExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Splash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Wave(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life);

	static HRESULT Load(void);						//テクスチャ読み込み
	static void Unload(void);						//テクスチャの破棄

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, EFFECT_TYPE type, D3DXCOLOR col, int Life);//初期化関数
	void Update(void);								//更新関数
	void Uninit(void);								//終了関数
	void Draw(void);								//描画関数


private:
	static LPDIRECT3DTEXTURE9 m_apTexture[EFFECT_TEXTURE_MAX];	//読み込むテクスチャ
	D3DXMATRIX	mtxWorld;						//ワールド計算用
	D3DXVECTOR3	m_Rot;							//プレイヤーの回転
	bool m_bLoop;								//アニメーションループ
	EFFECT_TYPE m_nType;						//種類
};

#endif // !PARTICLE_H_
