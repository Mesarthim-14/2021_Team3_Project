#ifndef _WAVE_H_
#define _WAVE_H_
//=============================================================================
//
// 上下運動のクラス	[wave.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"
#include "xfile.h"

//=========================================================================
// クラス定義
//=========================================================================
class CWave
{
public:
	CWave();		// コンストラクタ
	~CWave();		// デストラクタ

	static CWave *Create(float fTimeNum,
		float fPower, float fHeight);		// 影の生成
	HRESULT Init(float fTimeNum,
		float fPower, float fHeight);		// 初期化処理

	void Update(void);						// 更新処理
	float Wave(void);						// 上下動きの実装
	float Wave(int nCntV, int nCntH);		// 上下動きの実装

private:
	float m_fTime;		// 時間
	float m_fTimeNum;	// 時間
	float m_fPower;		// 上の力
	float m_fHeight;	// 波の高さ
};
#endif