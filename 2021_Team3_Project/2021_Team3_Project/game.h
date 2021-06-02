#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// ゲームの処理 [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define MAX_PLAYER (1)			// プレイヤーの数

//=======================================================================================
// 前方宣言
//=======================================================================================
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGame : public CModeBase
{
public:
	CGame();		// コンストラクタ
	~CGame();		// デストラクタ

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理
	void SetGame(void);				// ゲームの設定

	void CreatePlayer(void);		// プレイヤーの生成	
	void CreateMap(void);			// マップの生成	
	void CreateGround(void);		// 地面の生成	

	CCamera *GetCamera(void);	// カメラのポインタ情報
	CLight *GetLight(void);		// ライトのポインタ情報
	CPlayer *GetPlayer(void);	// プレイヤーのポインタ情報

private:	
	CCamera *m_pCamera;			// カメラのポインタ	
	CLight *m_pLight;			// ライトのポインタ
	CMeshField *m_pMeshField;	// メッシュフィールドのポインタ
	CBg *m_pBg;					// 背景のポインタ
	CPlayer *m_pPlayer;			// プレイヤーのポインタ
	LPD3DXFONT m_pFont;			// デバック用フォント
	int m_nTimeCounter;			// ゲームのカウンター
	bool m_bGameEnd;			// ゲームのエンドフラグ
};
#endif