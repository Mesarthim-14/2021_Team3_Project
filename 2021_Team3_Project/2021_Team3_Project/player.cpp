//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(20.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY				(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)									// キャラクターの回転する速度
#define SHIP_NUM						(0)										// 船のナンバー
#define MIN_MOVE						(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 移動量の最小値
#define SIZE							(D3DXVECTOR3 (500.0f,500.0f,1500.0f))	// サイズ
#define PARENT_NUM						(0)										// 親のナンバー
//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 初期化処理
		pPlayer->Init(pos, rot);
	}

	// ポインタを返す
	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// 座標　角度

	SetSpeed(PLAYER_SPEED);													// 速度の設定

	// サイズ設定
	SetSize(SIZE);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetPosOld(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// 角度の更新処理
	UpdateRot();

	// 親クラスの更新処理
	CCharacter::Update();

	// 体力が0になったら
	if (GetLife() <= 0)
	{
		// 死んだとき
		Death();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// モーション情報
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	// プレイヤーの移動処理
	Move();

	// 攻撃処理
	Attack();

	// 当たり判定処理
	Collision();
}

//=============================================================================
// 角度の更新処理
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CPlayer::Death(void)
{

}

//=============================================================================
// 移動の処理
//=============================================================================
void CPlayer::Move(void)
{
	// ローカル変数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// サウンドのポインタ
	float fAngle = GET_CAMERA_PTR->GetHorizontal();							// カメラの角度
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	D3DXVECTOR3 move = GetMove();											// 移動
	float fSpeed = GetSpeed();												// スピード
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// モーションの状態

	//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

		// 移動量設定
		move.x = sinf(fAngle + (fAngle2))* fSpeed;
		move.z = cosf(fAngle + (fAngle2))* fSpeed;

		// 角度の設定
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{

	}

	// 前に移動
	if (pKeyboard->GetPress(DIK_W))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		move.x = -sinf(fAngle)*fSpeed;
		move.z = -cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));
	}
	// 左に移動
	if (pKeyboard->GetPress(DIK_A))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		move.x = sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		move.z = cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));
	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_D))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		move.x = sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		move.z = cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	}

	// 移動量設定
	SetMove(move);

	// 入力されていない場合
	if (!pKeyboard->GetPress(DIK_W) && !pKeyboard->GetPress(DIK_S) &&
		!pKeyboard->GetPress(DIK_A) && !pKeyboard->GetPress(DIK_D))
	{
		// 移動量設定
		SetMove(MIN_MOVE);
	}

	// 古い座標取得
	D3DXVECTOR3 OldPos = GetOldPos();

	// 動いていなかったら
	if (OldPos == pos)
	{
		// 通常モーション
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// 攻撃処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Attack(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// SPACEキーを押した場合
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 移動量
		D3DXVECTOR3 bulletmove = ZeroVector3;

		// 向き取得
		D3DXVECTOR3 rot = GetRot();
		
		// モデルの情報取得
		CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

		// 船の位置取得
		D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

		// 弾生成
		CBullet::Create(pos, rot);
	}
}
//=============================================================================
// 当たり判定処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Collision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// モデルの情報取得
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// 位置取得
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// 位置取得
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
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
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// 位置取得
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// サイズ取得
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				//どこの面に当たったか取得
				//下
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					move.y = MIN_MOVE.y;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.y = MIN_MOVE.y;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.y = (size.y / DIVIDE_2) - (CharacterPos.y + CharacterSize.y / DIVIDE_2);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 上
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					move.y = MIN_MOVE.y;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.y = MIN_MOVE.y;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.y = (-size.y / DIVIDE_2) + (CharacterPos.y + CharacterSize.y / DIVIDE_2);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 左
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					move.x = MIN_MOVE.x;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.x = MIN_MOVE.x;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.x = (-size.x / DIVIDE_2) + (CharacterPos.x - CharacterSize.x / DIVIDE_2);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 右
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					move.x = MIN_MOVE.x;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.x = MIN_MOVE.x;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.x = (size.x / DIVIDE_2) + (CharacterPos.x + CharacterSize.x / DIVIDE_2);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 手前
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_BACK)
				{
					// 移動量0
					move.z = MIN_MOVE.z;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.z = MIN_MOVE.z;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.z = (size.z / DIVIDE_2) + (CharacterPos.z + CharacterSize.z / DIVIDE_2);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 奥
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_PREVIOUS)
				{
					// 移動量0
					move.z = MIN_MOVE.z;

					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.z = MIN_MOVE.z;

					// 位置
					pos.z = (-size.z / DIVIDE_2) + (CharacterPos.z + CharacterSize.z / DIVIDE_2);

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 移動量設定
					SetMove(move);

					// 位置設定
					SetPos(pos);
				}
				// 次のポインタ取得
				pScene= pSceneCur;
			} 
		}
	}
}