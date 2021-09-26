#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// ���f������ [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_DEFAULT_SIZE	(D3DXVECTOR3(1.0f, 1.0f, 1.0f))		// ���f���̒ʏ�̑傫��

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//=============================================================================
// ���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	//=============================================================================
	// ���C�̏��
	//=============================================================================
	struct RAY_DATA
	{
		float fAngle;
		float fRange;
		int nNum;
	};
	//=============================================================================
	// ���
	//=============================================================================
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
		STATE_MAX
	};
	CModel(PRIORITY Priority = PRIORITY_EFFECT);				// �R���X�g���N�^
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �C���X�^���X����
	void BindModel(CXfile::MODEL model);						// ���f���̐ݒ�
	void SubAlpha(float fAlpha);								// �����x�̌��Z
	void ShadowDraw(D3DXVECTOR3 rot);							// �e�̕`��
	void HasPtrDelete(void);									// �ێ��|�C���^�̊J������
	void SetShadowInfo(CXfile::MODEL model);					// �e�̏��ݒ�

	// Set�֐�
	void SetPos(const D3DXVECTOR3 pos)				{ m_pos = pos; }					// ���W�̐ݒ�
	void SetMove(const D3DXVECTOR3 move)			{ m_move = move; }					// �ړ��ʂ̐ݒ�
	void SetRot(const D3DXVECTOR3 rot)				{ m_rot = rot; }					// ���W�̏��
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; }					// �T�C�Y�̐ݒ�
	void SetTexPattern(int TexPattern)				{ m_nTexPattern = TexPattern; }		// �e�N�X�`���̃p�^�[��
	void SetLife(int nLife)							{ m_nLife = nLife; }				// ���C�t�̐ݒ�
	void SetColor(D3DXCOLOR color)					{ m_Color = color; }				// �F�̐ݒ�
	void SetAlphaNum(float fAlphaNum)				{ m_fAlphaNum = fAlphaNum; }		// �����x�̐ݒ�
	void SetScale(D3DXVECTOR3 scale)				{ m_scale = scale; }				// �g�嗦
	void SetState(STATE state)						{ m_State = state; }				// ��Ԑݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture)	{ m_apTexture = pTexture; }			// �e�N�X�`���̐ݒ�
	void SetRay_Data(RAY_DATA Ray_Info) { m_RayData = Ray_Info; }						// ���C�̏��ݒ�

	// Get�֐�
	D3DXVECTOR3 &GetPos(void)			{ return m_pos; }				// ���W�̏��
	D3DXVECTOR3 &GetMove(void)			{ return m_move; }				// �ړ��ʂ̏��
	D3DXVECTOR3 GetSize(void)const		{ return m_size; }				// �T�C�Y�̐ݒ�
	D3DXVECTOR3 &GetRot(void)			{ return m_rot; }				// �p�x�̐ݒ�
	D3DXCOLOR GetColor(void)			{ return m_Color; }				// �F�̏��
	D3DXMATRIX GetMtxWorld(void)const	{ return m_mtxWorld; }			// ���[���h�}�g���N�X
	LPD3DXMESH GetMesh(void)const		{ return m_Model.pMesh; }		// ���b�V�����
	LPD3DXBUFFER GetBuffMat(void)		{ return m_Model.pBuffMat; }	// �o�b�t�@���
	DWORD GetNumMat(void)				{ return m_Model.dwNumMat; }	// �}�g���N�X�̐�
	int GetTexPattern(void)				{ return m_nTexPattern; }		// �e�N�X�`��
	int GetLife(void)					{ return m_nLife; }				// ���C�t�̐ݒ�
	float GetAlphaNum(void)				{ return m_fAlphaNum; }			// �����x�̒l
	STATE GetState(void)				{ return m_State; }				// ��Ԏ擾
	RAY_DATA GetRay_Data(void)			{ return m_RayData; }			// ���C�̏��擾
private:
	LPDIRECT3DTEXTURE9 *m_apTexture;	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_scale;				// �g�嗦
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXCOLOR m_Color;					// �F
	CXfile::MODEL m_Model;				// ���f���̍\����
	int m_nTexPattern;					// �e�N�X�`���̃p�^�[����
	int m_nLife;						// ���C�t
	float m_fAlphaNum;					// �����x�̒l
	STATE m_State;						// ���
	RAY_DATA m_RayData;					// ���C�̏��
	// �e�̐����p
	CShadow *m_pShadow;		// �e�̃|�C���^
};
#endif 