//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "texture.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"
#include "map.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(1.0f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限
#define PARENT_NUM				(0)							// 親のナンバー
//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_nLife = 0;
	m_fSpeed = 0.0f;
	m_bArmor = false;
	m_nStateCounter = 0;
	m_pMotion = nullptr;
	m_nParts = 0;
	m_apModelAnime.clear();
	m_bLanding = false;
	m_State = STATE_NORMAL;
	m_bUseShadow = false;
	m_RayData = { ZERO_FLOAT,ZERO_FLOAT,ZERO_INT };
	m_bGravity = true;
	m_bHitMap = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 引数の代入
	m_pos = pos;
	m_rot = rot;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter::Uninit()
{
	for (auto &nCount : m_apModelAnime)
	{
		// !nullcheck
		if (nCount != nullptr)
		{
			//メモリの削除
			delete nCount;
			nCount = nullptr;
		}
	}

	// クリア
	m_apModelAnime.clear();

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//メモリの削除
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter::Update()
{
	// 重力
	Gravity();

	// falseの場合
	if (m_bHitMap == false)
	{
		// 移動量加算
		m_pos += m_move;
	}
	// 無敵時間のとき
	if (m_bArmor == true)
	{
		// カウンターを進める
		m_nStateCounter++;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter::Draw()
{
	// 描画処理
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	for (auto &model : m_apModelAnime)
	{
		if (model != nullptr)
		{
			model->Draw(m_rot);
		}
	}

	if (m_bUseShadow)
	{
		// 影の描画
		for (auto &shadow : m_apModelAnime)
		{
			if (shadow != nullptr)
			{
				shadow->ShadowDraw(m_rot);
			}
		}
	}
}

//=============================================================================
// モデルの生成
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFileのポインタ取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルパーツの設定
		m_nParts = pXfile->GetModelParts(FileNum);

		//モデルパーツ数分繰り返す
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			// ローカル変数取得
			CModelAnime *pModelAnime = nullptr;
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);
			vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

			// nullcheck
			if (pModelAnime == nullptr)
			{
				// インスタンス生成
				pModelAnime = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));

				// !nullcheck
				if (pModelAnime != nullptr)
				{
					pModelAnime->SetModel(model.at(nCntModel));

					//親モデルの場合
					if (nCntModel == 0)
					{
						pModelAnime->SetParent(nullptr);
					}
					//子モデルの場合
					else
					{
						//自分の親情報を設定する
						pModelAnime->SetParent(m_apModelAnime.at(ModelFile.nParent));
					}
				}

				// 情報を入れる
				m_apModelAnime.push_back(pModelAnime);
			}
		}
		// nullcheck
		if (m_pMotion == nullptr)
		{
			// インスタンス生成
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// モデルアニメーション
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// モーションの更新処理
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 重力の処理
//=============================================================================
void CCharacter::Gravity(void)
{
	// 重力をかける
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// 落下

	// 地面の判定
	if (m_pos.y <= GROUND_RIMIT)
	{
		Landing(GROUND_RIMIT);
	}
}

//=============================================================================
// 着地の処理
//=============================================================================
void CCharacter::Landing(float fHeight)
{
	m_move.y = 0.0f;
	m_pos.y = fHeight;

	// 着地の状態
	if (m_bLanding == false)
	{
		m_bLanding = true;
	}
}
//=============================================================================
// レイの当たり判定
// Author : SugawaraTsukasa
//=============================================================================
void CCharacter::RayCollision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_MAP);

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

				// レイの数が0より多い場合
				if (m_RayData.nNum > ZERO_INT)
				{
					// 位置取得
					Pos.x = GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// レイの情報
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, ((CMap*)pScene), m_RayData.fAngle, m_RayData.fRange, m_RayData.nNum);

					// trueの場合
					if (Ray_Info.bHit == true)
					{
						// 移動を0に
						SetMove(ZeroVector3);

						// 位置
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						SetPos(Pos);
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 影の回転を反映させるか
//=============================================================================
void CCharacter::SetShadowRotCalculation(void)
{
	// モデルの描画
	for (auto &model : m_apModelAnime)
	{
		if (model != nullptr)
		{
			model->SetRotCalculation(true);
		}
	}
}