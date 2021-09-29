//=============================================================================
// プレイヤー弾 [player_bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "model_box.h"
#include "enemy.h"
#include "player_bullet.h"
#include "effect.h"

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(40.0f)								// 移動量
#define PARENT_NUM	(0)									// 親のナンバー
#define DAMAGE		(100)								// ダメージ

//水しぶき																			
#define SPLASH_POS			(D3DXVECTOR3(0, 1, 0))									//位置
#define SPLASH_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 80.0f))						//大きさ
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))						//移動力
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//色
#define SPLASH_LIFE			(200)													//体力

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet::CPlayer_Bullet(PRIORITY Priority) : CBullet (Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet::~CPlayer_Bullet()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet * CPlayer_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer_Bulletのポインタ
	CPlayer_Bullet *pPlayer_Bullet = nullptr;

	// nullcheck
	if (pPlayer_Bullet == nullptr)
	{
		// メモリ確保
		pPlayer_Bullet = new CPlayer_Bullet;

		// !nullcheck
		if (pPlayer_Bullet != nullptr)
		{
			// 初期化処理
			pPlayer_Bullet->Init(pos, rot);

			// 箱生成
			//CModel_Box::Create(pos, rot, pPlayer_Bullet);
		}
	}
	// ポインタを返す
	return pPlayer_Bullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// XFile名設定
	SetXFileNum(CXfile::XFILE_NUM_BULLET);

	// 初期化処理
	CBullet::Init(pos, ZeroVector3);

	// 移動
	D3DXVECTOR3 move = ZeroVector3;

	// 弾の移動
	move.x = -sinf(rot.y) *MOVE_VALUE;
	move.z = -cosf(rot.y) *MOVE_VALUE;

	// 移動量設定
	SetMove(move);

	// 箱生成
	//CModel_Box::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Uninit(void)
{
	// 終了処理
	CBullet::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Update(void)
{
	// 更新処理
	CBullet::Update();

	// 当たり判定
	Collision();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Draw(void)
{
	// 描画処理
	CBullet::Draw();
}
//=============================================================================
// 当たり判定処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Collision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// 船の位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) 	// nullptrになるまで回す
			{
				// トップ代入
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// 位置取得
				CharacterPos.x = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// サイズ取得
				D3DXVECTOR3 CharacterSize = ((CEnemy*)pScene)->GetSize();

				//エフェクト発生
				for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
				{
					// パーティクル生成
					CEffect::Create(CharacterPos,
						SPLASH_SIZE, SPLASH_MOVE, SPLASH_COLOR,
						CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
				}

				// 判定
				if (CCollision::CollisionRectangleAndRectangle(pos, CharacterPos, size, CharacterSize) == true)
				{
					// ライフ設定
					((CEnemy*)pScene)->Hit(DAMAGE);

					// 終了
					Uninit();

					return;
				}

				// 次に代入
				pScene = pSceneCur;
			}
		}
	}
}
