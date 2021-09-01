#ifndef _CHARACTER_BOX_H_
#define _CHARACTER_BOX_H_
//=============================================================================
// 箱 [character_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "character.h"
#include "model.h"

//=============================================================================
// 箱クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CCharacter_Box: public CModel
{
public:
	CCharacter_Box(PRIORITY Priority = PRIORITY_CHARACTER);										// コンストラクタ
	~CCharacter_Box();																			// デストラクタ
	static CCharacter_Box *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);												// 初期化処理
	void Uninit(void);																			// 終了処理
	void Update(void);																			// 更新処理
	void Draw(void);																			// 描画処理
private:
	CCharacter *m_pCharacter;		// CCharacterのポインタ
};
#endif