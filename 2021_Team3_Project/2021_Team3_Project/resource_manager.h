#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
//
// リソースマネージャー処理 [resource_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
class CXfile;
class CSound;

//=============================================================================
// リソースマネージャークラス
//=============================================================================
class CResourceManager
{
public:
	~CResourceManager();									// デストラクタ

	HRESULT Init(void);										// 初期化処理
	void LoadAll(void);										// 全てのロード処理
	void UnLoadAll(void);									// 全てのアンロード

	static CResourceManager *GetInstance(void);				// インスタンス取得関数

	// Get関数
	CTexture *GetTextureClass(void) { return m_pTexture; }	// テクスチャの情報
	CXfile *GetXfileClass(void) { return m_pXFile; }		// テクスチャの情報
	CSound *GetSoundClass(void) { return m_pSound; }		// サウンドの情報

private:
	CResourceManager();								// コンストラクタ
	static CResourceManager *m_pResourceManager;	// 自身のポインタ
	CTexture *m_pTexture;							// テクスチャのポインタ
	CXfile *m_pXFile;								// Xファイルのポインタ
	CSound *m_pSound;								// サウンドのポインタ
};

#endif