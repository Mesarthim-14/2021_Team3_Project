#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// X�t�@�C���Ǘ��w�b�_�[ [xfile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CXfile
{
public:
	//=============================================================================
	//�@���f�����̍\����
	//=============================================================================
	struct MODEL
	{
		LPD3DXMESH pMesh;							// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;						// �}�e���A�����ւ̃|�C���^
		DWORD dwNumMat;								// �}�e���A�����̐�
		vector<LPDIRECT3DTEXTURE9> apTexture;		// �e�N�X�`���̐�
	};

	//=============================================================================
	//�@���f���t�@�C�����̍\����
	//=============================================================================
	struct MODELFILE
	{
		string aFileName;			// �t�@�C���l�[��
		D3DXVECTOR3 offsetPos;		// �ʒu�̃I�t�Z�b�g���
		D3DXVECTOR3 offsetRot;		// �����̃I�t�Z�b�g���
		int nParent;				// �e���
	};

	//=============================================================================
	// X�t�@�C�����f���̔ԍ��̗񋓌^
	//=============================================================================
	enum XFILE_NUM
	{
		XFILE_NUM_NONE = -1,			// �����l
		XFILE_NUM_BG,					// �w�i
		XFILE_NUM_MAX
	};

	//=============================================================================
	// �K�w�\�����f���̔ԍ�
	//=============================================================================
	enum HIERARCHY_XFILE_NUM
	{
		HIERARCHY_XFILE_NUM_NONE = -1,			// �����l
		HIERARCHY_XFILE_NUM_PLAYER,				// �v���C���[���f��
		HIERARCHY_XFILE_NUM_MAX					// �ő吔
	};

	CXfile();							// �R���X�g���N�^
	~CXfile();							// �f�X�g���N�^

	static CXfile *Create(void);		// �C���X�^���X����

	// �P�̃��f��
	HRESULT ModelLoad(void);			// ���f�����[�h
	void ModelUnLoad(void);				// ���f���A�����[�h

	// �K�w�\�����f��
	HRESULT HierarchyReadFile(void);	// �K�w�\���̂��郂�f���ǂݍ���
	HRESULT HierarchyModelLoad(void);	// �K�w�\���̃��f�����[�h
	void HierarchyModelUnLoad(void);	// �K�w�\���̃��f���A�����[�h
	void SetHierarchyFileName(void);	// �t�@�C���̖��O��ݒ�

	// Get�֐�
	MODEL GetXfile(XFILE_NUM Tex_Num);																			// ���f���̏��
	MODELFILE GetModelFile(int nCount, HIERARCHY_XFILE_NUM FileNum) { return m_apModelFile[FileNum].at(nCount); }	// ���f���p�[�c�̏��
	int GetModelParts(HIERARCHY_XFILE_NUM FileNum) { return m_nMaxParts[FileNum]; }								// ���f���̃p�[�c��
	string GetModelFileName(HIERARCHY_XFILE_NUM FileNum) { return m_pFileName[FileNum]; }						// ���f���t�@�C���̖��O
	vector<MODEL> GetHierarchyXfile(HIERARCHY_XFILE_NUM FileNum) { return m_apHierarchyModel[FileNum]; }
	LPDIRECT3DTEXTURE9 *GetXfileTexture(XFILE_NUM TexNum);

private:
	MODEL m_aXfile[XFILE_NUM_MAX];							// X�t�@�C�����̍\����
	vector<std::string> m_aXfileName;						// X�t�@�C���̖��O

	// �K�w�\���̃��f���p
	vector<MODEL> m_apHierarchyModel[HIERARCHY_XFILE_NUM_MAX];			// �K�w�\�����f���̃|�C���^
	vector<MODELFILE> m_apModelFile[HIERARCHY_XFILE_NUM_MAX];			// �K�w�\�����f���̃|�C���^
	vector<std::string> m_aHierarchyXfileName;							// �K�w�\��X�t�@�C���̖��O
	string m_pFileName[HIERARCHY_XFILE_NUM_MAX];						// �t�@�C���̖��O
	int m_nMaxParts[HIERARCHY_XFILE_NUM_MAX];							// �t�@�C�����Ƃ̃p�[�c��
};
#endif
