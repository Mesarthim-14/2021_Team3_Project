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

//=======================================================================================
// 前方宣言
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CMap;
class CBoss_Shark;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGame : public CModeBase
{
public:
	enum ENEMY_OBSTACLE_TYPE
	{
		ENEMY_OBSTACLE_TYPE_MIN = 0,
		ENEMY_OBSTACLE_TYPE_SHIP,
		ENEMY_OBSTACLE_TYPE_SCAFFOLDING,
		ENEMY_OBSTACLE_TYPE_TORPEDO,
		ENEMY_OBSTACLE_TYPE_ROCK,
		ENEMY_OBSTACLE_TYPE_MAX
	};
	//=============================================================================
	//　敵生成ファイル情報の構造体
	//=============================================================================
	struct ENEMY_FILE_DATA
	{
		D3DXVECTOR3 Pos;		// 位置のオフセット情報
		D3DXVECTOR3 Rot;		// 向きのオフセット情報
		ENEMY_OBSTACLE_TYPE Type;		// 種類情報
	};

	CGame();		// コンストラクタ
	~CGame();		// デストラクタ

	HRESULT Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	void SetGame(void);								// ゲームの設定

	void CreatePlayer(void);						// プレイヤーの生成	
	void CreateMap(void);							// マップの生成	
	void CreateGround(void);						// 地面の生成
	void CreateEnemy_Obstacle(string pEnemyFile);	// 敵生成関数
	void RoadEnemyFile(string pEnemyFile);			// 敵の生成ファイル読み込み
	void DrawPlayerPos(void);						// プレイヤーの位置書き込み
	void CreateBossMap(void);						// ボスマップ生成
	void BossTransition(void);						// ボス戦遷移
	void ModeTransition(void);						// モード遷移
	void Boss_Enemy_Create(void);					// ボス戦敵生成
													// Set関数
	void SetbBoss(bool bBoss) { m_bBoss = bBoss; }	// ボス戦の判定
	void SetbBossTransition(bool bBossTransition) { m_bBossTransition = bBossTransition; }	// ボス戦遷移の判定

	// Get関数
	CCamera *GetCamera(void)		{ return (CCamera*)m_pCamera; }	// カメラのポインタ情報
	CLight *GetLight(void)			{ return m_pLight; }			// ライトのポインタ情報
	CPlayer *GetPlayer(void)		{ return m_pPlayer; }			// プレイヤーのポインタ情報
	CMap *GetMap(void)				{ return m_pMap; }				// マップのポインタ取得
	bool GetbBoss(void)				{ return m_bBoss; }				// ボスのbool取得
	bool GetbBossTransition(void)	{ return m_bBossTransition; }	// ボス遷移判定取得

private:
	// ポインタ
	CCameraGame *m_pCamera;					// カメラのポインタ	
	CLight *m_pLight;						// ライトのポインタ
	CMeshField *m_pMeshField;				// メッシュフィールドのポインタ
	CBg *m_pBg;								// 背景のポインタ
	CPlayer *m_pPlayer;						// プレイヤーのポインタ
	CMap * m_pMap;							// マップのポインタ
	CBoss_Shark *m_pBoss_Shark;				// ボスのポインタ
	ENEMY_FILE_DATA *m_pEnemyFileData;		// 敵のファイルデータ
	int m_nEnemyNum;						// 敵数
	bool m_bGameEnd;						// ゲームのエンドフラグ
	bool m_bBossTransition;					// ボス戦に遷移したか
	bool m_bBoss;							// ボス戦か

	LPD3DXFONT m_pFont;						// デバック用フォント
};
#endif