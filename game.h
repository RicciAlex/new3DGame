//=============================================================================
//
// game.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "object.h"
#include "hitbox.h"
#include <functional>

//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;
class CTimer;
class CPauseMenu;
class CGoal;


class CGame : public CMode
{
public:

	//�X�e�[�W
	enum STAGE
	{
		FIRST_STAGE = 0,

		STAGE_MAX
	};

	CGame();						//�R���X�g���N�^
	~CGame() override;				//�f�X�g���N�^

	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	void AddTime(const float fMilliseconds);		//���Ԃ̒ǉ�����

	void SetPlayer(CPlayer* pPlayer);		//�v���C���[�̐ݒ菈��
	CPlayer* GetPlayer(void);				//�v���C���[�̎擾����
	CGoal* GetGoal(void);					//�S�[���̎擾����

protected:

	void LoadMap(char* pPass, CObject::TextType fieldTexture);		//�}�b�v�̃��[�h����

private:

	void LoadVector2(FILE* pFile, D3DXVECTOR2 &vector2);
	void LoadVector3(FILE* pFile, D3DXVECTOR3 &vector3);
	void LoadColor(FILE* pFile, D3DXCOLOR &col);

	void LoadMeshField(FILE* pFile, CObject::TextType fieldTexture);

	void LoadHitbox(FILE* pFile);
	void SetLoadedHitboxType(char* pLoadedType, CHitbox::HITBOX_TYPE &type);
	void SetLoadedHitboxEffect(char* pLoadedType, CHitbox::INTERACTION_EFFECT &effect);

	void LoadGoal(FILE* pFile, CGoal* pGoal);
	void LoadNail(FILE* pFile);
	void LoadSpikeTrap(FILE* pFile);
	void LoadStar(FILE* pFile);
	void LoadShurikenTrap(FILE* pFile);
	void LoadTriggerablePlatform(FILE* pFile);
	void LoadMovingCube(FILE* pFile);
	void LoadAccelerationFloor(FILE* pFile);
	void LoadCameraSetter(FILE* pFile);
	void LoadCheckpoint(FILE* pFile);
	void LoadFallBoard(FILE* pFile);
	void LoadFirePipe(FILE* pFile);
	void LoadFogbot(FILE* pFile);
	void LoadPendulumClock(FILE* pFile);
	void LoadGem(FILE* pFile);

	CPlayer* m_pPlayer;				//�v���C���[�ւ̃|�C���^
	CTimer*  m_pTimer;				//�^�C�}�[�ւ̃|�C���^
	CPauseMenu* m_pPauseMenu;		//�|�[�Y���j���[�ւ̃|�C���^
	CGoal*   m_pGoal;				//�S�[���ւ̃|�C���^

};



#endif