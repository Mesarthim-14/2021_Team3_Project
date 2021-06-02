#ifndef _MESH_3D_H_
#define _MESH_3D_H_
//=============================================================================
//
// 3D���b�V�������N���X�w�b�_�[ [mesh_3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene_base.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MESH_WIDTH				(6)				// ������
#define MESH_HEIGHT				(4)				// ������
#define MESH_WIDTH_SIZE			(12000.0f)		// �T�C�Y
#define MESH_HEIGHT_SIZE		(12000.0f)		// �T�C�Y

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMesh3d : public CSceneBase
{
public:
	//=============================================================================
	// �񋓌^
	//=============================================================================
	enum MESH_TYPE
	{
		MESH_TYPE_NONE = -1,	// �����l
		MESH_TYPE_TUBE_6,		// 6�p�`�̉~��
		MESH_TYPE_PILLAR_6,		// 6�p�`�̉~��
		MESH_TYPE_MAX			// �ő�l
	};

	// ���p�`�����擾����\����
	struct CYLINDER
	{
		int nNumX;							// ���p�`���̒l
		int nNumY;							// ���p�`���̒l
	};

	// 3D���b�V���̍\����
	struct MESH_3D
	{
		CYLINDER CylinderNum;	// ���p�`��
		D3DXVECTOR2 size;		// �T�C�Y
	};

	CMesh3d(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CMesh3d();										// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;	// ����������
	virtual void Uninit(void) = 0;									// �I������
	virtual void Update(void) = 0;									// �X�V����
	virtual void Draw(void);										// �`�揈��

	static HRESULT ReadFile(void);									// �t�@�C���ǂݍ���

	// Set�֐�
	void SetNumVertex(const int nNumVertex)										{ m_nNumVertex = nNumVertex; }						// ���_��
	void SetNumIndex(const int nNumIndex)										{ m_nNumIndex = nNumIndex; }						// �C���f�b�N�X��
	void SetNumPolygon(const int nNumPolygon)									{ m_nNumPolygon = nNumPolygon; }					// �|���S����
	void SetCylinderNum(const CYLINDER &CylinderNum, const  MESH_TYPE &typeNum)	{ m_Mesh3D[typeNum].CylinderNum = CylinderNum; }	// ���p�`���ݒ肷��
	void BindIdxBuff(const LPDIRECT3DINDEXBUFFER9 IdxBuff)						{ m_pIdxBuff = IdxBuff; }							// �o�b�t�@�ԍ��̐ݒ�
	void BindMtxWorld(const D3DXMATRIX mtxWorld)								{ m_mtxWorld = mtxWorld; }							// �}�g���N�X���
	void SetOneSize(const D3DXVECTOR2 &OneSize)									{ m_OneSize = OneSize; }							// ��̃u���b�N�̑傫��
	void SetMeshNum(const MESH_TYPE MeshNum)									{ m_MeshNum = MeshNum; }							// ���b�V���̔ԍ��̐ݒ�
	
	// Get�֐�
	int &GetNumVertex(void)							{ return m_nNumVertex; }					// ���_���̏��
	int &GetNumIndex(void)							{ return m_nNumIndex; }						// �C���f�b�N�X���̏��
	int &GetNumPolygon(void)						{ return m_nNumPolygon; }					// �|���S�����̏��
	CYLINDER &GetCylinderNum(MESH_TYPE typeNum)		{ return m_Mesh3D[typeNum].CylinderNum; }	// ���p�`���̏��
	MESH_TYPE &GetMeshNum(void)						{ return m_MeshNum; }						// ���b�V���̔ԍ�
	D3DXVECTOR2 &GetOneSize(void)					{ return m_OneSize; }						// �T�C�Y
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff(void)			{ return m_pIdxBuff; }						// �o�b�t�@�ԍ��̏��
	D3DXMATRIX GetMtxWorld(void)					{ return m_mtxWorld; }						// �}�g���N�X���
	static MESH_3D GetMesh3D(MESH_TYPE MeshNum)		{ return m_Mesh3D[MeshNum]; }				// ���b�V���̏��

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// �o�b�t�@�̔ԍ�
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nNumVertex;							// �����_��
	int m_nNumIndex;							// ���C���f�b�N�X��
	int m_nNumPolygon;							// ���|���S����
	D3DXVECTOR2 m_OneSize;						// ��̃|���S���̑傫��
	static MESH_3D m_Mesh3D[MESH_TYPE_MAX];		// 3D���b�V���̍\���̏��
	MESH_TYPE m_MeshNum;						// ���b�V���̔ԍ�
	D3DXVECTOR3 m_move;							// �ړ�
};

#endif