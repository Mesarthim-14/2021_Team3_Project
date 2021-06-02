#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_
//=============================================================================
//
// シーンベースクラスヘッダー [scene_base.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// シーンベースクラス
//=============================================================================
class CSceneBase : public CScene
{
public:
	CSceneBase(PRIORITY Priority = PRIORITY_0);									// コンストラクタ
	virtual ~CSceneBase();														// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;				// 初期化処理
	virtual void Uninit(void) = 0;												// 終了処理
	virtual void Update(void) = 0;												// 更新処理
	virtual void Draw(void) = 0;												// 描画処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// テクスチャの設定

protected:

	// Set関数
	virtual void SetPos(const D3DXVECTOR3 &pos)					{ m_pos = pos; }			// 座標
	virtual void SetSize(const D3DXVECTOR3 &size)				{ m_size = size; }			// サイズ
	virtual void SetRot(const D3DXVECTOR3 &rot)					{ m_rot = rot; }			// 角度		
	virtual void SetColor(const D3DXCOLOR &col)					{ m_col = col; }			// 色
	void BindVtxBuff(const LPDIRECT3DVERTEXBUFFER9 pVtxBuff)	{ m_pVtxBuff = pVtxBuff; }	// 頂点バッファ

	// Get関数
	D3DXVECTOR3 &GetPos(void)					{ return m_pos; }							// 座標
	D3DXVECTOR3 &GetSize(void)					{ return m_size; }							// サイズ
	D3DXCOLOR &GetColor(void)					{ return m_col; };							// 色
	D3DXVECTOR3 &GetRot(void)					{ return m_rot; };							// 回転量
	LPDIRECT3DTEXTURE9 GetTexture(void)			{ return m_pTexture; }						// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)	{ return m_pVtxBuff; }						// バッファ情報

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// バッファ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_col;						// 色
	D3DXVECTOR3 m_rot;						// 回転量
};

#endif