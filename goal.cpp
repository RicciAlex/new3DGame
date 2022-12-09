//=============================================================================
//
// goal.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "goal.h"
#include "application.h"
#include "game.h"
#include "player.h"

//�R���X�g���N�^
CGoal::CGoal()
{

}

//�f�X�g���N�^
CGoal::~CGoal()
{

}

//����������
HRESULT CGoal::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CGoal::Uninit(void)
{
	CModel::Uninit();
}

//�X�V����
void CGoal::Update(void)
{
	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

		float fDistance = D3DXVec3Length(&distance);

		if (fDistance <= 80.0f)
		{
			CApplication::SetFade(CApplication::MODE_RESULTS);
		}
	}
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = new CGoal;

	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	pGoal->SetPos(pos);
	pGoal->SetModel(CModel::MODEL_FLAG);
	pGoal->SetShadowHeight(pos.y);

	return pGoal;
}