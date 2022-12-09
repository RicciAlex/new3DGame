//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "sound.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CSound;
class CCamera;
class CDebugProc;
class CMode;
class CFade;
class CGame;
//class CMenu;
//class CMessage;

//�A�v���P�[�V�����̃N���X
class CApplication
{
public:
	enum Mode
	{
		MODE_TITLE = 0,
		MODE_FIRST_STAGE,
		MODE_RESULTS,
		MODE_RANKING,

		MODE_MAX
	};

	enum FADE
	{
		FADE_NONE = 0,	// �������Ă��Ȃ����
		FADE_IN,		// �t�F�[�h�C��(���X�ɓ����ɂ�����)
		FADE_OUT,		// �t�F�[�h�A�E�g(���X�ɕs�����ɂ�����)

		FADE_MAX
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static CRenderer* GetRenderer(void);				//�����f�B���O�C���X�^���X�̎擾����
	static HWND GetWindow(void);						//�E�C���h�E�̎擾����
	static CSound* GetSound(void);						//�T�E���h�̎擾����
	static CCamera* GetCamera(void);					//�J�����̎擾����
	static const bool GetFade(void);					//�t�F�[�h�̎擾����
	static void SetFade(const bool bFade);				//�t�F�[�h�̐ݒ菈��
	static void SetFade(Mode mode);						// ���[�h�̐ݒ菈��

	static Mode GetMode(void);							// ���[�h�̎擾����
	static void SetMode(Mode mode);						//���[�h�̐ݒ菈��
	static CGame* GetGame(void);						//�Q�[�����[�h�̎擾����

	static bool GetPause(void);							// �|�[�Y�̎擾����
	static void SetPause(const bool bPause);			// �|�[�Y�̐ݒ菈��


private:



	static int m_nStageSelect;							//�I�𒆂̃X�e�[�W�Z���N�g
	static bool m_bPause;								//�|�[�Y���ł��邩�ǂ���
	static bool m_bFade;

	static HWND m_hWnd;									//�N���C�G���g���
	static CRenderer* m_pRenderer;						//�����f�B���O�C���X�^���X�ւ̃|�C���^
	static CInputKeyboard* m_pKeyboard;					//�C���v�b�g�f�o�C�X�ւ̃|�C���^
	static CSound* m_pSound;							//�T�E���h�̃C���X�^���X�ւ̃|�C���^
	static CFade* m_pFade;								//�t�F�[�h�̃C���X�^���X�ւ̃|�C���^
	static CCamera* m_pCamera;							//�J�����̃C���X�^���X�ւ̃|�C���^
	static CMode* m_pMode;								//���[�h�̃C���X�^���X�ւ̃|�C���^
	static CDebugProc* m_pDebug;						//�f�o�b�O�e�L�X�g�̃C���X�^���X

	static Mode m_mode;		//���݃��[�h
	static Mode m_modeNext;	//���̃��[�h
};

#endif // !APPLICATION_H
