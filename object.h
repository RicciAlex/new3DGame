//=============================================================================
//
// object.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_H
#define OBJECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CObject
{
public:

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			//xyz���W
		float rhw;					//rhw
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;			//xyz���W
		D3DXVECTOR3 nor;			//�@��
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	struct VERTEX_LINE
	{
		D3DXVECTOR3 pos;			//xyz���W
		D3DCOLOR col;				//�J�[���[
	};

	//�e�N�X�`���̎��
	enum TextType
	{
		TEXTURE_NULL = 0,

		TEXTURE_BLOCK,
		TEXTURE_CHARACTERS,
		TEXTURE_TITLE,
		TEXTURE_PRESS_ENTER,
		TEXTURE_WASD_KEY,
		TEXTURE_PRESS_KEY,
		TEXTURE_SPACE_KEY,
		TEXTURE_STAGE_LOGO,
		TEXTURE_GEM_ICON,
		TEXTURE_FOG,
		TEXTURE_METAL,
		TEXTURE_IRON,
		TEXTURE_OLD_WOOD,
		TEXTURE_GREEN,
		TEXTURE_BLUE,
		TEXTURE_GRASS,
		TEXTURE_ARROW_TILE_UP,
		TEXTURE_ARROW_TILE_RIGHT,
		TEXTURE_ARROW_TILE_DOWN,
		TEXTURE_ARROW_TILE_LEFT,
		TEXTURE_GUIDE_ARROW,

		TEXTURE_GEAR_BG,
		TEXTURE_ICE,
		TEXTURE_SNOW,

		TEXTURE_STAR_UI,

		TEXTURE_CIRCLE_EFFECT,
		TEXTURE_MAGIC_CIRCLE_EFFECT,
		TEXTURE_CIRCLE,

		TEXTURE_TYPE_MAX
	};

	static const int MaxObject = 5000;					//�I�u�W�F�N�g�̍ő吔

	CObject();											//�R���X�g���N�^
	CObject(int nPriority);								//�R���X�g���N�^ (1 <= priority <= 5)
	virtual~CObject();									//�f�X�g���N�^
														
	virtual HRESULT Init(void) = 0;						//����������
	virtual void Uninit(void) = 0;						//�I������
	virtual void Update(void) = 0;						//�X�V����
	virtual void Draw(void) = 0;						//�`�揈��
														
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//�ʒu�̐ݒ菈��
	
	void Release(void);									//�C���X�^���X��̏I������
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//�ʒu�̎擾����
	void SetPriority(int nPriority);					//�v���C�I���e�B�̐ݒ菈��
														
	//�ÓI�֐�
	static void ReleaseAll(void);						//�S���̏I������
	static void UpdateAll(void);						//�S���̍X�V����
	static void DrawAll(void);							//�S���̕`�揈��
	static CObject** GetObj(void);						//�I�u�W�F�N�g�̎擾����

	static int random(const int low, const int high);				//������Ԃ�����

private:								

	static const int Max_Priority = 5;					//�v���C�I���e�B�̍ő�l
	int m_nIdx;											//���̃C���X�^���X�̔z��̃C���f�b�N�X
	int m_nPriority;									//�`�揇
	bool m_bDeath;										//���S�t���O

	static CObject* m_pTop[Max_Priority];				//�擪�̃I�u�W�F�N�g�ւ̃|�C��
	static CObject* m_pCurrent[Max_Priority];			//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|���^
	CObject* m_pPrev;									//�O�̃I�u�W�F�N�g�ւ̃|���^
	CObject* m_pNext;									//���̃I�u�W�F�N�g�ւ̃|���^
};

#endif