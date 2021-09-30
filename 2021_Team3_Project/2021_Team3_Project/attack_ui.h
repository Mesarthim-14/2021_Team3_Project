#ifndef _ATTACK_UI_H_
#define _ATTACK_UI_H_
//=============================================================================
// 攻撃の操作UIクラス [attack_ui.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "control_ui.h"

//=============================================================================
// クラス定義
// Author : Konishi Yuuto
//=============================================================================
class CAttackUi : public CControlUi
{
public:
	CAttackUi(PRIORITY Priority = PRIORITY_UI);			// コンストラクタ
	~CAttackUi();										// デストラクタ
	static CAttackUi *Create(CModelAnime *pPtr);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理

private:
};
#endif