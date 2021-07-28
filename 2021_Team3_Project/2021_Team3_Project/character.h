#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクタークラスヘッダ  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene
{
public:
	//=============================================================================
	// キャラクターの種類
	//=============================================================================
	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NONE = 0,	// 初期値
		CHARACTER_TYPE_PLAYER,		// プレイヤー
		CHARACTER_TYPE_MAX,			// 最大数
	};

	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
		STATE_MAX
	};

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	virtual ~CCharacter();											// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	virtual void Uninit();											// 終了処理
	virtual void Update();											// 更新処理
	virtual void Draw();											// 描画処理

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// モデルの生成
	void ModelAnimeUpdate(void);									// モデルアニメーション
	void Gravity(void);												// 重力
	void Landing(float fHeight);									// 着地

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;								// キャラクター状態
	//virtual void UpdateMotionState(void) = 0;						// モーションの状態
	virtual void Attack(void) = 0;									// 攻撃の処理
	virtual void Move(void) = 0;									// 移動関数
	virtual void Death(void) = 0;									// 死んだときの処理

	// Set関数
	void SetPos(D3DXVECTOR3 &pos)			{ m_pos = pos; }			// 座標の設定
	void SetPosOld(D3DXVECTOR3 &posOld)		{ m_posOld = posOld; }		// 座標の設定
	void SetMove(D3DXVECTOR3 &move)			{ m_move = move; }			// 移動量の設定
	void SetRot(D3DXVECTOR3 &rot)			{ m_rot = rot; }			// 角度の設定
	void SetSize(D3DXVECTOR3 &size)			{ m_size = size; }			// サイズ設定
	void SetLife(int nLife)					{ m_nLife = nLife; }		// ライフの設定
	void SetSpeed(float fSpeed)				{ m_fSpeed = fSpeed; }		// 速度の設定
	void SetMotion(int nMotionState);									// モーションの設定
	void SetState(STATE state)				{ m_State = state; }		// 状態設定
	void SetLanding(bool bLanding)			{ m_bLanding = bLanding; }	// 着地
	// Get関数
	D3DXVECTOR3 &GetPos(void)				{ return m_pos; }						// 現在の座標情報
	D3DXVECTOR3 &GetOldPos(void)			{ return m_posOld; }					// 古い座標情報
	D3DXVECTOR3 &GetRot(void)				{ return m_rot; }						// 角度情報
	D3DXVECTOR3 &GetMove(void)				{ return m_move; }						// 移動量の情報
	D3DXVECTOR3 &GetSize(void)				{ return m_size; }						// サイズ取得
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime.at(nCount); }	// モーションのカウント情報
	int GetPartsNum(void)					{ return m_apModelAnime.size(); }		// パーツ数取得
	CMotion *GetMotion(void)				{ return m_pMotion; }					// モーションのポインタ情報
	int GetLife(void)						{ return m_nLife; }						// ライフの情報
	int GetStateCounter(void)				{ return m_nStateCounter; }				// 状態カウンターの情報
	float GetSpeed(void)					{ return m_fSpeed; }					// スピードの情報
	bool GetArmor(void)						{ return m_bArmor; }					// 無敵時間
	STATE GetState(void) { return m_State; }										// 状態取得

private:
	vector<CModelAnime*> m_apModelAnime;	// モデルパーツ用ポインタ
	CMotion *m_pMotion;						// モーションクラスのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_posOld;					// 古い座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_rot;						// 現在の回転
	D3DXVECTOR3 m_size;						// サイズ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	int m_nLife;							// 体力
	int m_nStateCounter;					// 状態のカウンター
	int m_nParts;							// パーツ数
	float m_fSpeed;							// 移動量
	bool m_bArmor;							// 無敵フラグ
	bool m_bLanding;						// 着地フラグ
	STATE m_State;							// 状態
};
#endif