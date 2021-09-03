//=============================================================================
// 弾 [bullet.cpp]
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
#include "modelanime.h"
#include "character_box.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define PARENT_NUM	(0)		// 親のナンバー

// キャラクターの位置
#define POS			(D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43))
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CCharacter_Box::CCharacter_Box(PRIORITY Priority)
{
	m_pCharacter = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CCharacter_Box::~CCharacter_Box()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CCharacter_Box * CCharacter_Box::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter)
{
	// CCharacter_Boxのポインタ
	CCharacter_Box *pBox = nullptr;

	// nullcheck
	if (pBox == nullptr)
	{
		// メモリ確保
		pBox = new CCharacter_Box;

		// !nullcheck
		if (pBox != nullptr)
		{
			// ポインタ代入
			pBox->m_pCharacter = pCharacter;

			// 初期化処理
			pBox->Init(pos, ZeroVector3);
		}
	}
	// ポインタを返す
	return pBox;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CCharacter_Box::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BOX);

		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ取得
	D3DXVECTOR3 size = m_pCharacter->GetSize();

	// 拡大率の設定
	SetScale(size);

	// 初期化処理
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacter_Box::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacter_Box::Update(void)
{
	// 更新処理
	CModel::Update();

	// 死亡状態の場合
	if (m_pCharacter->GetState() == CCharacter::STATE_DEAD)
	{
		// 終了
		Uninit();

		return;
	}

	// ポインタ取得
	CModelAnime *pAnime = m_pCharacter->GetModelAnime(PARENT_NUM);

	// 位置設定
	SetPos(POS);
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacter_Box::Draw(void)
{
	// 描画処理
	CModel::Draw();
}