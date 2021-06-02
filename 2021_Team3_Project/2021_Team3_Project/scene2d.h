#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=======================================================================================
// 
// 2Dポリゴン描画クラス処理 [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "scene_base.h"

//=======================================================================================
// シーン2Dクラス定義
//=======================================================================================
class CScene2D : public CSceneBase
{
public:
	CScene2D(PRIORITY Priority = PRIORITY_0);							// コンストラクタ
	~CScene2D();														// デストラクタ

	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理

	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// アニメーション情報初期化
	void InitScroll(int nSpeed, float fDivision);						// 画像スクロールの設定
	void UpdateAnimation(void);											// アニメーションの更新
	void UpdateScroll(void);											// 画像スクロールの更新
	void ScaleUp(float fScaleUp);										// 拡大関数
	void FlashPolygon(int nFlashFlame);									// ポリゴンの点滅

	// Set関数
	void SetCol(D3DXCOLOR col);											// 色の設定
	void SetRotation(float rotasion);									// 回転の設定
	void SetScale(const float &fScale);									// 拡大の値設定
	void SetSubFlashNum(float fSubNum) { m_fSubNum = fSubNum; }			// 点滅の値設定

	// Get関数
	float GetScale(void) { return m_fScaleNum; }						// 拡大の値情報

private:
	int m_nCountAnim;			// アニメーションテクスチャ
	int m_nCountAnimPattern;	// アニメーションのパターン
	int m_nCounterAnim;			// アニメーションのカウンター
	int m_nPatternAnim;			// アニメーションのパターン数
	int m_nSpeedTexture;		// テクスチャの移動速度
	int m_nLoop;				// ループするかどうか
	float m_fDivisionCounter;	// スクロールのカウンター
	float m_fDivisionBaseNum;	// スクロールの移動量
	float m_fRotasion;			// 回転用変数
	float m_fScaleNum;			// 拡大用変数
	float m_fSubFlashNum;		// ポリゴンの点灯用
	float m_fSubNum;			// ポリゴンの点灯用
	int m_nFlashFlame;			// 点灯用のカウンター
	bool m_bDisappearFlag;		// 点滅用のフラグ
};

#endif // !_SCENE2D_H_