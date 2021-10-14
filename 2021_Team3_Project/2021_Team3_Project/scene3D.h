#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3Dポリゴンクラスヘッダー [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CScene3D :public CSceneBase
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_EFFECT);				// コンストラクタ
	virtual ~CScene3D();										// デストラクタ
	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理
	void CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 頂点の設定

	// Set関数
	void SetMove(D3DXVECTOR3 move);								// 移動量
	void SetPosision(D3DXVECTOR3 pos);							// 座標の更新
	void SetAlpha(bool bAlpha);									// アルファテスト
	void SetAlphaNum(int nAlphaNum);							// アルファテストの値
	void SetBlend(bool bBlend);									// 加算合成
	void SetInverse(bool bInverse);								// 逆行列を行うか
	void SubAlpha(float fAlphaNum);								// 透明度の減算
	void InitAnimation(D3DXVECTOR2 TexInfo, int nLoop);			// アニメーション情報初期化
	void UpdateAnimation(void);									// アニメーションの更新
	void ScaleUp(float fScale);									// 拡大処理
	void SetColor(D3DXCOLOR color);								// カラーの設定

private:
	D3DXMATRIX	m_mtxWorld;		// ワールドマトリクス
	D3DXVECTOR3 m_move;			// 移動量
	int m_nCountAnim;			// アニメーションテクスチャ
	int m_nCountAnimPattern;	// アニメーションのパターン
	int m_nCounterAnim;			// アニメーションのカウンター
	int m_nPatternAnim;			// アニメーションのパターン数
	int m_nLoop;				// ループするかどうか
	int m_nLife;				// ライフ
	int m_nAlphaTestNum;		// 透明の値
	float m_fScaleNum;			// 拡大値
	float m_fAlphaNum;			// 透明度
	bool m_bAlpha;				// 透明を使うフラグ
	bool m_bBlend;				// 加算合成
	bool m_bInverse;			// 逆行列のフラグ
};
#endif