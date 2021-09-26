#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// モデル処理 [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_DEFAULT_SIZE	(D3DXVECTOR3(1.0f, 1.0f, 1.0f))		// モデルの通常の大きさ

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//=============================================================================
// モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	//=============================================================================
	// レイの情報
	//=============================================================================
	struct RAY_DATA
	{
		float fAngle;
		float fRange;
		int nNum;
	};
	//=============================================================================
	// 状態
	//=============================================================================
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
		STATE_MAX
	};
	CModel(PRIORITY Priority = PRIORITY_EFFECT);				// コンストラクタ
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// インスタンス生成
	void BindModel(CXfile::MODEL model);						// モデルの設定
	void SubAlpha(float fAlpha);								// 透明度の減算
	void ShadowDraw(D3DXVECTOR3 rot);							// 影の描画
	void HasPtrDelete(void);									// 保持ポインタの開放処理
	void SetShadowInfo(CXfile::MODEL model);					// 影の情報設定

	// Set関数
	void SetPos(const D3DXVECTOR3 pos)				{ m_pos = pos; }					// 座標の設定
	void SetMove(const D3DXVECTOR3 move)			{ m_move = move; }					// 移動量の設定
	void SetRot(const D3DXVECTOR3 rot)				{ m_rot = rot; }					// 座標の情報
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; }					// サイズの設定
	void SetTexPattern(int TexPattern)				{ m_nTexPattern = TexPattern; }		// テクスチャのパターン
	void SetLife(int nLife)							{ m_nLife = nLife; }				// ライフの設定
	void SetColor(D3DXCOLOR color)					{ m_Color = color; }				// 色の設定
	void SetAlphaNum(float fAlphaNum)				{ m_fAlphaNum = fAlphaNum; }		// 透明度の設定
	void SetScale(D3DXVECTOR3 scale)				{ m_scale = scale; }				// 拡大率
	void SetState(STATE state)						{ m_State = state; }				// 状態設定
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture)	{ m_apTexture = pTexture; }			// テクスチャの設定
	void SetRay_Data(RAY_DATA Ray_Info) { m_RayData = Ray_Info; }						// レイの情報設定

	// Get関数
	D3DXVECTOR3 &GetPos(void)			{ return m_pos; }				// 座標の情報
	D3DXVECTOR3 &GetMove(void)			{ return m_move; }				// 移動量の情報
	D3DXVECTOR3 GetSize(void)const		{ return m_size; }				// サイズの設定
	D3DXVECTOR3 &GetRot(void)			{ return m_rot; }				// 角度の設定
	D3DXCOLOR GetColor(void)			{ return m_Color; }				// 色の情報
	D3DXMATRIX GetMtxWorld(void)const	{ return m_mtxWorld; }			// ワールドマトリクス
	LPD3DXMESH GetMesh(void)const		{ return m_Model.pMesh; }		// メッシュ情報
	LPD3DXBUFFER GetBuffMat(void)		{ return m_Model.pBuffMat; }	// バッファ情報
	DWORD GetNumMat(void)				{ return m_Model.dwNumMat; }	// マトリクスの数
	int GetTexPattern(void)				{ return m_nTexPattern; }		// テクスチャ
	int GetLife(void)					{ return m_nLife; }				// ライフの設定
	float GetAlphaNum(void)				{ return m_fAlphaNum; }			// 透明度の値
	STATE GetState(void)				{ return m_State; }				// 状態取得
	RAY_DATA GetRay_Data(void)			{ return m_RayData; }			// レイの情報取得
private:
	LPDIRECT3DTEXTURE9 *m_apTexture;	// テクスチャのポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_move;					// 移動量
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXVECTOR3 m_scale;				// 拡大率
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXCOLOR m_Color;					// 色
	CXfile::MODEL m_Model;				// モデルの構造体
	int m_nTexPattern;					// テクスチャのパターン数
	int m_nLife;						// ライフ
	float m_fAlphaNum;					// 透明度の値
	STATE m_State;						// 状態
	RAY_DATA m_RayData;					// レイの情報
	// 影の生成用
	CShadow *m_pShadow;		// 影のポインタ
};
#endif 