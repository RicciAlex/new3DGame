//=============================================================================
//
// spawnTrigger.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _SPAWN_TRIGGER_H
#define _SPAWN_TRIGGER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "triggerablePlatform.h"
#include <vector>

//=============================================================================
//�O���錾
//=============================================================================

class CSpawnTrigger : public CObject
{
public:

	CSpawnTrigger();					//�R���X�g���N�^
	~CSpawnTrigger() override;			//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void AddObject(CObject* pObj, const float fHeight);	//�I�u�W�F�N�g�̒ǉ�����
	void AddTriggerPlatform(CTriggerablePlatform* pTrigger);	//�g���K�[�̒ǉ�����

	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	static CSpawnTrigger* Create(void);					//��������
	static CSpawnTrigger* Create(const D3DXVECTOR3 pos);					//��������

private:

	static const D3DXVECTOR3 DEFAULT_POS;				//�f�B�t�H���g�̈ʒu

	D3DXVECTOR3 m_pos;									//�ʒu

	CTriggerablePlatform* m_pTrigger;					//�g���K�[�ւ̃|�C���^
	std::vector <CObject*> m_vSpawnObj;					//�I�u�W�F�N�g�ւ̃|�C���^
	std::vector <float>	  m_vObjHeight;					//�I�u�W�F�N�g��Y���W
};



#endif