#ifndef _ROTATE_UI_H_
#define _ROTATE_UI_H_
//=============================================================================
// 移動の操作UIクラス [rotate_ui.h]
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
class CRotateUi : public CControlUi
{
public:
	CRotateUi(PRIORITY Priority = PRIORITY_UI);			// コンストラクタ
	~CRotateUi();										// デストラクタ
	static CRotateUi *Create(CModelAnime *pPtr);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理

private:
};
#endif