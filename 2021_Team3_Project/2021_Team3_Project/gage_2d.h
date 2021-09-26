//=============================================================================
// 2Dゲージ [gage_2d.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _GAGE_2D_H_
#define _GAGE_2D_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene_base.h"

//=============================================================================
// ゲージクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CGage_2D :public CSceneBase
{
public:
	CGage_2D(PRIORITY nPriority = PRIORITY_UI);								// コンストラクタ
	~CGage_2D();															// デストラクタ
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理関数
	virtual void Uninit(void);												// 終了処理関数
	virtual void Update(void);												// 更新処理関数
	virtual void Draw(void);												// 描画処理関数

																			// Set関数
	void SetPosition(const D3DXVECTOR3 pos);								// 位置設定処理関数
	void SetColor(const D3DXCOLOR col);										// 色設定処理関数
	void SetAlphaNum(int nAlphaNum) { m_nAlphaNum = nAlphaNum; }			// アルファテストの値設定関数
	void SetGageNum(int nGageNum);											// ゲージの値設定処理関数
	void SetMaxGageNum(int nMaxGageNum);									// ゲージの最大値設定
private:
	D3DXMATRIX m_mtxWorld;				// ワールド座標
	int m_nGageNum;						// ゲージの値
	float m_fMaxGageNum;				// ゲージの最大
	float m_fGageNum;					// ゲージの値
	int m_nAlphaNum;					// アルファテストの値
};
#endif