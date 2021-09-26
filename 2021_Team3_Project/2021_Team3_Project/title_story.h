#ifndef _TITLE_STORY_H_
#define _TITLE_STORY_H_
//=============================================================================
//
// タイトルストーリークラス [title_story.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode_base.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
// クラス定義
//=============================================================================
class CTitleStory : public CModeBase
{
public:
	CTitleStory();						// コンストラクタ
	~CTitleStory();						// デストラクタ

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理
	void ModeTransition(void);			// モード遷移
	void SkipSentence(void);			// 文章のスキップ

	void CreateBg(void);			// 文章のスキップ
	void CreateSentence0(void);		// 文章の生成
	void CreateSentence1(void);		// 文章の生成
	void CreateSentence2(void);		// 文章の生成
	void CreateSentence3(void);		// 文章の生成

private:
	vector<CScene2D*> m_pObject2D;						// 2Dオブジェクト
	int m_nSentenceNum;									// 文章の番号
	int m_nTimeCounter;									// 時間のカウント
	bool m_bEnd;										// 遷移可能フラグ

	// 文章の生成を促す関数ポインタ
	typedef void(CTitleStory::*SENTENCE_FUNC)();
	vector<SENTENCE_FUNC> m_CreateSentence = 
	{ &CTitleStory::CreateSentence0 , &CTitleStory::CreateSentence1,
		&CTitleStory::CreateSentence2, &CTitleStory::CreateSentence3 };

};
#endif