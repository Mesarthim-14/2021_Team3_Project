#ifndef _WATER_H_
#define _WATER_H_
//=============================================================================
//
// 水のクラス [water.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "meshfield.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CWave;

//=============================================================================
// 水クラス
//=============================================================================
class CWater : public CMeshField
{
public:
	CWater(PRIORITY = PRIORITY_0);				// コンストラクタ
	~CWater();									// デストラクタ
	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理
	void Wave(void);							// 波の処理
	void SetMatrix(void);						// マトリクスの設定
	static CWater*Create(void);					// インスタンス生成
	static HRESULT LoadShaderFile(void);		// シェーダファイルの読み込み

private:
	D3DXMATRIX m_mtxWorld;			// ワールドマトリクス

	// エフェクト作成
	static LPD3DXEFFECT m_pEffect;							// エフェクト用ポインタ
	LPDIRECT3DVOLUMETEXTURE9 m_pNoiseVolumeTexture;	// ノイズテクスチャ
	LPDIRECT3DCUBETEXTURE9 m_pEnvironmentTexture;	// キューブテクスチャ
	float m_fFileTime;										// ファイルの経過時間
	D3DXMATRIXA16 m_MatPlayer;								// プレイヤーのマトリクス
	CWave *m_pWave;											// 波の移動
};

#endif