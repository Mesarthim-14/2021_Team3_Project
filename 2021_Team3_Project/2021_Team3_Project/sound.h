#ifndef _SOUND_H_
#define _SOUND_H_

//================================================
//
// �T�E���h���� [sound.h]
// Author : Konishi Yuuto
//
//================================================

#include "main.h"
#include "xaudio2.h"

//================================================
//�N���X�錾
//================================================
class CSound
{
public:
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0
		SOUND_LABEL_MAX,
	};

	enum SOUND_LOOP
	{
		SOUND_LOOP_ON = -1,				//���[�v����
		SOUND_LOOP_OFF,					//���[�v���Ȃ�
	};

	CSound();							// �R���X�g���N�^
	~CSound();							// �f�X�g���N�^

	static CSound *Create(void);		// �C���X�^���X����
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	HRESULT Play(SOUND_LABEL label);	// �T�E���h�Đ�
	void Stop(SOUND_LABEL label);		// �T�E���h�X�g�b�v
	void StopAll(void);					// �S�ẴT�E���h���~

private:
	struct PARAM
	{
		char *m_pFilename;																			// �t�@�C����
		SOUND_LOOP isLoop;																			// ���[�v���邩�ǂ���
	};

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;																	// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;												// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};										// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};														// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};														// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif