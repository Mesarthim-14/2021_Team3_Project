#ifndef _MODEL_BOX_H_
#define _MODEL_BOX_H_
//=============================================================================
// 箱 [character_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//============================================================================="
#include "model.h"

//=============================================================================
// 箱クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CModel_Box : public CModel
{
public:
	CModel_Box(PRIORITY Priority = PRIORITY_CHARACTER);									// コンストラクタ
	~CModel_Box();																		// デストラクタ
	static CModel_Box *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel *pModel);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// 初期化処理
	void Uninit(void);																	// 終了処理
	void Update(void);																	// 更新処理
	void Draw(void);																	// 描画処理
private:
	CModel *m_pModel;																// CCharacterのポインタ
};
#endif