#ifndef _MODELANIME_H_
#define _MODELANIME_H_
//=============================================================================
//
// 階層構造用のモデル処理 [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_OLD_MTX_WORLD		(5)			// ワールドマトリクスの配列

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//=============================================================================
//階層モデルクラス
//=============================================================================
class CModelAnime
{
public:
	CModelAnime();		// コンストラクタ
	~CModelAnime();		// デストラクタ

	static CModelAnime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// インスタンス生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// 初期化処理
	void Draw(D3DXVECTOR3 rot);												// 描画処理
	void HasPtrDelete(void);												// 保持ポインタの開放処理
	void ShadowDraw(D3DXVECTOR3 rot);										// 影の描画

																			// Set関数
	void SetParent(CModelAnime *pParent);									// 親の設定
	void SetRot(const D3DXVECTOR3 rot);										// 向き設定
	void SetPosAnime(const D3DXVECTOR3 posAnime);							// アニメーションパーツの座標
	void SetRotAnime(const D3DXVECTOR3 rotAnime);
	void SetModel(CXfile::MODEL model);										// モデル情報の設定
	D3DXMATRIX SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent);          // 影の情報の設定
	void SetRotCalculation(bool bFlag) { m_bRotCalculation = bFlag; }		// 角度の計算フラグの設定

																			// Get情報
	D3DXVECTOR3 GetPos(void)const;											// 座標情報
	D3DXVECTOR3 GetPosAnime(void)const;										// アニメーション座標情報
	D3DXVECTOR3 GetRot(void)const;											// 角度の情報
	D3DXVECTOR3 GetRotAnime(void)const;										// アニメーション角度情報
	D3DXMATRIX GetMtxWorld(void);											// ワールドマトリクス情報
	D3DXMATRIX GetOldMtxWorld(void);										// 古いワールドマトリクスの情報
	LPD3DXMESH GetMesh(void) { return m_model.pMesh; }						// モデル情報取得
private:
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR3 m_posAnime;							// アニメーション用の位置
	D3DXVECTOR3 m_rotAnime;							// アニメーション用の向き
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	CModelAnime *m_pParent;							// 親情報のポインタ
	D3DXMATRIX m_OldMtxWorld;						// 古いワールド座標
	D3DXMATRIX m_OldMtxWorld1[MAX_OLD_MTX_WORLD];	// 5フレームまでの古い座標
	CXfile::MODEL m_model;							// モデル情報

													// 影の生成用
	CShadow *m_pShadow;		// 影のポインタ
	bool m_bRotCalculation;	// 角度の計算フラグ
};

#endif 