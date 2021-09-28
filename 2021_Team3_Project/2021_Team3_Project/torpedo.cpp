//=============================================================================
// 魚雷 [torpedo.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "torpedo.h"
#include "renderer.h"
#include "map.h"
#include "model_box.h"

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE			(D3DXVECTOR3(1000.0f,800.0f,1000.0f))		// サイズ
#define ROT				(D3DXVECTOR3(rot.x,rot.y + m_fAngle,rot.z))	// 向き
#define MOVE_VALUE		(10.0f)										// 移動量
#define DECISION_LENGTH	(5000.0f)									// 扇の長さ
#define FAN_DIR			(D3DXVECTOR3(1.0f, 0.0f, 0.0f))				// 弧線方向
#define ANGLE_90		(D3DXToRadian(90.0f))						// 90度
#define ANGLE_270		(D3DXToRadian(270.0f))						// 270度
#define ANGLE_0			(D3DXToRadian(0.0f))						// 0度
#define ANGLE_360		(D3DXToRadian(360.0f))						// 360度
#define FAN_COS			(cosf(D3DXToRadian(180.0f / 2.0f)))			// cosfに
#define RAY_HIT_RANGE	(250.0f)									// レイの範囲
#define RAY_NUM			(1)											// レイの本数
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo::CTorpedo(PRIORITY Priority) : CModel(Priority)
{
	m_bAttackDecision	= false;
	m_bMove				= false;
	m_fAngle			= ZERO_FLOAT;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo::~CTorpedo()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo * CTorpedo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CTorpedoのポインタ
	CTorpedo *pTorpedo = nullptr;

	// nullcheck
	if (pTorpedo == nullptr)
	{
		// メモリ確保
		pTorpedo = new CTorpedo;

		// !nullcheck
		if (pTorpedo != nullptr)
		{
			// 初期化処理
			pTorpedo->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pTorpedo;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CTorpedo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TORPEDO);
		 
		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ設定
	SetSize(SIZE);

	// 箱生成
	//CModel_Box::Create(pos, rot, this);

	// 初期化処理
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Update(void)
{
	// 更新処理
	CModel::Update();

	// 扇の判定
	FanDecision();

	// 攻撃判定がtrueの場合
	if (m_bAttackDecision == true)
	{
		// 移動判定がfalseの場合
		if (m_bMove == false)
		{
			// プレイヤーのポインタ取得
			CPlayer *pPlayer = GET_PLAYER_PTR;

			// 位置取得
			D3DXVECTOR3 pos = GetPos();

			// 向き取得
			D3DXVECTOR3 rot = GetRot();

			// !nullcheck
			if (pPlayer != nullptr)
			{
				// 位置座標取得
				D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

				// 角度
				m_fAngle = atan2f((pos.x - PlayerPos.x), (pos.z - PlayerPos.z));
			}
			
			// レイの情報
			CModel::RAY_DATA Ray_Data = { ROT.y, RAY_HIT_RANGE,RAY_NUM };

			// レイの情報設定
			SetRay_Data(Ray_Data);

			// 向き
			SetRot(ROT);

			// 移動判定をtrueに
			m_bMove = true;
		}
		// 移動処理
		Move();
	}

	// 当たり判定
	Collision();

	// ゲーム取得
	CGame *pGame = (CGame*)CManager::GetModePtr();

	// !nullchrck
	if (pGame != nullptr)
	{
		// ボス戦に遷移したか
		bool bBossTransition = pGame->GetbBossTransition();

		// ボス戦に遷移した場合
		if (bBossTransition == true)
		{
			// 終了
			Uninit();

			return;
		}
	}
	// レイの当たり判定
	//RayCollision();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Draw(void)
{
	// 描画処理
	CModel::Draw();
}
//=============================================================================
// 移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Move(void)
{
	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 弾の移動
	move.x = -sinf(m_fAngle) *MOVE_VALUE;
	move.z = -cosf(m_fAngle) *MOVE_VALUE;

	// 移動設定
	SetMove(move);
}
//=============================================================================
// 当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Collision(void)
{
	// 船の位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// プレイヤー位置座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// プレイヤーサイズ取得
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// 判定
	if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
	{
		// 終了処理
		Uninit();

		return;
	}
}
//=============================================================================
// 当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::FanDecision(void)
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// 位置取得
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// プレイヤーの位置座標取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// ベクトル
		D3DXVECTOR3 Vec = ZeroVector3;

		// 点と扇のベクトル
		Vec.x = PlayerPos.x - Pos.x;
		Vec.z = PlayerPos.z - Pos.z;

		// 長さ算出
		float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

		// 長さの比較
		if (fVec_Length > DECISION_LENGTH)
		{
			// 攻撃判定をtrueに
			m_bAttackDecision = false;
			// 処理の終了
			return;
		}

		// 向き取得
		D3DXVECTOR3 Rot = GetRot();

		// 向き
		float fRot = ZERO_FLOAT;

		// 前を向いてるか後ろを向いてるか
		if (Rot.y > ANGLE_90 && Rot.y < ANGLE_270 || Rot.y < ANGLE_90 && Rot.y > -ANGLE_90)
		{
			// 向き
			fRot = Rot.y - ANGLE_90;
		}
		//右を向いてるか左を向いてるか
		if (Rot.y > ANGLE_0 && Rot.y < ANGLE_360 || Rot.y < ANGLE_0 && Rot.y > -ANGLE_0)
		{
			// 向き
			fRot = Rot.y + ANGLE_90;
		}

		// 向き
		D3DXVECTOR3 FanDir = FAN_DIR;

		// 回転
		D3DXVECTOR3 Rotate_ArcDir = ZeroVector3;

		// ベクトルを回転させる
		Rotate_ArcDir.x = FanDir.x * cosf(fRot) + FanDir.z * -sinf(fRot);
		Rotate_ArcDir.z = FanDir.x * sinf(fRot) + FanDir.z * cosf(fRot);

		// 単位ベクトル
		D3DXVECTOR3 Normal_Vec = ZeroVector3;

		// 単位ベクトルにする
		Normal_Vec.x = Vec.x / fVec_Length;
		Normal_Vec.z = Vec.z / fVec_Length;

		// 内積計算
		float fdot = Normal_Vec.x * Rotate_ArcDir.x + Normal_Vec.z * Rotate_ArcDir.z;

		// 扇の範囲をcosにする
		float fcos = FAN_COS;

		// 点が扇の範囲内にあるかを比較する
		if (fcos < fdot)
		{
			// 攻撃判定をtrueに
			m_bAttackDecision = true;
		}
	}
}
//=============================================================================
// レイの当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::RayCollision(void)
{
	//// 位置取得
	//D3DXVECTOR3 pos = GetPos();

	//// 向き取得
	//D3DXVECTOR3 rot = GetRot();

	//// マップのポインタ取得
	//CMap *pMap = GET_MAP_PTR;

	//// レイの情報
	//CCollision::RAY_INFO Ray_Info;

	//// レイの当たり判定
	//Ray_Info = CCollision::RayCollision(pos, GET_MAP_PTR, rot.y, RAY_HIT_RANGE, RAY_NUM);

	//// trueの場合
	//if (Ray_Info.bHit == true)
	//{
	//	// 戻す
	//	pos -= (D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y)));

	//	// 位置設定
	//	SetPos(pos);

	//	return;
	//}
}