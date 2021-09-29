//=============================================================================
// マップ [bullet.cpp]
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
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "map.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE		(D3DXVECTOR3(80.0f,80.0f,80.0f))	// サイズ
#define POS_Y_MIN	(0.0f)								// Y座標最小値
#define PARENT_NUM	(0)									// 親の名前
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NORMAL;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CMap::~CMap()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CMap * CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	// CBulletのポインタ
	CMap *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// メモリ確保
		pMap = new CMap;

		// !nullcheck
		if (pMap != nullptr)
		{
			// 代入
			pMap->m_Type = type;

			// 初期化処理
			pMap->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pMap;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル
		CXfile::MODEL model;

		// TYPE_NORMALの場合
		if (m_Type == TYPE_NORMAL)
		{
			// モデル情報取得
			model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
		}
		// TYPE_BOSSの場合
		if (m_Type == TYPE_BOSS)
		{
			// モデル情報取得
			model = pXfile->GetXfile(CXfile::XFILE_NUM_BOSS_MAP);
		}
		// モデルの情報を渡す
		BindModel(model);
	}

	// 初期化処理
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Update(void)
{
	// 更新処理
	CModel::Update();


	//RayCollision();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Draw(void)
{
	// 描画処理
	CModel::Draw();
}
//=============================================================================
// レイの当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::RayCollision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// nullcheck
	if (pScene == nullptr)
	{
		//===============================================================
		// 敵以外の親子関係のあるオブジェクト
		//===============================================================
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_CHARACTER);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 Pos = ZeroVector3;

				// レイの情報取得
				CCharacter::RAY_DATA RayData = ((CCharacter*)pScene)->GetRay_Data();

				// レイの数が0より多い場合
				if (RayData.nNum > ZERO_INT)
				{
					// 位置取得
					Pos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// レイの情報
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// trueの場合
					if (Ray_Info.bHit == true)
					{
						// ヒットマップ
						((CCharacter*)pScene)->SetHitMap(true);

						// 移動を0に
						((CCharacter*)pScene)->SetMove(ZeroVector3);

						// 位置
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// 位置設定
						((CCharacter*)pScene)->SetPos(Pos);
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
		//===============================================================
		// 親子関係のある敵
		//===============================================================
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 Pos = ZeroVector3;

				// レイの情報取得
				CCharacter::RAY_DATA RayData = ((CCharacter*)pScene)->GetRay_Data();

				// レイの数が0より多い場合
				if (RayData.nNum > ZERO_INT)
				{
					// 位置取得
					Pos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// レイの情報
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// trueの場合
					if (Ray_Info.bHit == true)
					{
						
						// 移動を0に
						((CCharacter*)pScene)->SetMove(ZeroVector3);

						// 位置
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// 位置設定
						((CCharacter*)pScene)->SetPos(Pos);
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}

		//===============================================================
		// 親子関係のない敵
		//===============================================================
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_TORPEDO);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 Pos = ((CModel*)pScene)->GetPos();

				// レイの情報取得
				CModel::RAY_DATA RayData = ((CModel*)pScene)->GetRay_Data();

				// レイの数が0より多い場合
				if (RayData.nNum > ZERO_INT)
				{
					// レイの情報
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// trueの場合
					if (Ray_Info.bHit == true)
					{
						// 移動を0に
						((CModel*)pScene)->SetMove(ZeroVector3);

						// 位置
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// 位置設定
						((CModel*)pScene)->SetPos(Pos);

						// 位置設定
						((CModel*)pScene)->Uninit();

						return;
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}