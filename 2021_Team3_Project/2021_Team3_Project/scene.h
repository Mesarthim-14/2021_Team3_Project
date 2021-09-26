#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NUM (4112)

//=============================================================================
// シーンクラス
//=============================================================================
class CScene
{
public:
	//=========================================================================
	//描画の優先順位の列挙型
	//=========================================================================
	enum PRIORITY
	{
		PRIORITY_0 = 0,
		PRIORITY_1,
		PRIORITY_OBSTACLE,	// 障害物
		PRIORITY_MODEL,		// モデル
		PRIORITY_CHARACTER,	// キャラクター
		PRIORITY_ENEMY,		// 敵
		PRIORITY_TORPEDO,	// 魚雷
		PRIORITY_MAP,		// マップ
		PRIORITY_EFFECT,	// エフェクト
		PRIORITY_PARTICLE,	// エフェクト
		PRIORITY_3D_UI,		// UI
		PRIORITY_UI,		// UI
		PRIORITY_FADE,		// FADE
		PRIORITY_MAX		// 優先順位の最大数
	};

	CScene(PRIORITY Priority = PRIORITY_0);						// コンストラクタ
	virtual ~CScene();											// デストラクタ
	static void ReleaseAll(void);								// 全てのオブジェクトをリリース
	static void UpdateAll(void);								// 全てのオブジェクトを更新
	static void DrawAll(void);									// 全てのオブジェクトを描画

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;								// 終了処理
	virtual void Update(void) = 0;								// 更新処理
	virtual void Draw(void) = 0;								// 描画処理

	CScene *GetTop(int nCount);									// シーンの情報受け取り
	CScene *GetNext(void);										// 次の情報を受け取る
	static void SetPause(bool Pause);							// ポーズの情報
	void DeathRelease(void);									// 死亡フラグのリリース

protected:
	void Release(void);					// オブジェクトを開放

private:
	static CScene *m_pTop[PRIORITY_MAX];	// 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[PRIORITY_MAX];	// 現在のオブジェクトへのポインタ
	CScene *m_pPrev;						// 前のオブジェクトへのポインタ
	CScene *m_pNext;						// 次のオブジェクトへのポインタ
	PRIORITY m_nPriority;					// 描画の優先順位
	bool m_bDeath;							// 死亡フラグ
	bool m_bLate;							// 描画を遅らせる処理
	static bool m_bPause;					// ポーズの情報
};

#endif