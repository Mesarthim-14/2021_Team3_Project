//=============================================================================
// 弾 [bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "bullet.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY							(0.1f)							// 重力
#define MOVE_VALUE						(40.0f)							// 移動量
#define ANGLE_180						(D3DXToRadian(180))				// 180度
#define ANGLE_90						(D3DXToRadian(90))				// 90度
#define LENGTH							(-600.0f)						// 距離
#define BULLET_Y						(500.0f)						// 弾のY軸
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::CBullet(PRIORITY Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::~CBullet()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBulletのポインタ
	CBullet *pBullet = nullptr;

	// nullcheck
	if (pBullet == nullptr)
	{
		// メモリ確保
		pBullet = new CBullet;

		// !nullcheck
		if (pBullet != nullptr)
		{
			// 初期化処理
			pBullet->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pBullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BULLET);

		// モデルの情報を渡す
		BindModel(model);
	}

	// ライフ設定
	SetLife(1000);

	// 発射位置
	D3DXVECTOR3 bulletpos = ZeroVector3;

	// 移動
	D3DXVECTOR3 move = ZeroVector3;

	//座標を求める
	bulletpos.x = pos.x - cosf(rot.y + ANGLE_90) * LENGTH;
	bulletpos.z = pos.z + sinf(rot.y + ANGLE_90) * LENGTH;
	bulletpos.y = BULLET_Y;

	// 弾の移動
	move.x = sinf(rot.y + ANGLE_180) *MOVE_VALUE;
	move.z = cosf(rot.y + ANGLE_180) *MOVE_VALUE;

	// 移動量設定
	SetMove(move);

	// 初期化処理
	CModel::Init(bulletpos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Update(void)
{
	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 移動
	move.y -= GRAVITY;

	// 移動量設定
	SetMove(move);

	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Draw(void)
{
	// 描画処理
	CModel::Draw();
}