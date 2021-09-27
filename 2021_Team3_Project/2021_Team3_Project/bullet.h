#ifndef _BULLET_H_
#define _BULLET_H_
//=============================================================================
// 弾 [bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "xfile.h"
#include "model.h"

//=============================================================================
// 弾クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBullet : public CModel
{
public:
	CBullet(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CBullet();													// デストラクタ
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	void CreateSplash(void);									// 水しぶき生成関数
	void Death(void);											// 死亡処理関数

	void SetXFileNum(CXfile::XFILE_NUM XfileNum) { m_XfileNum = XfileNum; }		// Xfile名取得
private:
	CXfile::XFILE_NUM m_XfileNum;	// Xfile名
};
#endif