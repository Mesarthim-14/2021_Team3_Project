#ifndef _ROCK_H_
#define _ROCK_H_
//=============================================================================
// 岩 [rock.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// 岩クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CRock : public CModel
{
public:
	CRock(PRIORITY Priority = PRIORITY_OBSTACLE);			// コンストラクタ
	~CRock();												// デストラクタ
	static CRock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
};
#endif