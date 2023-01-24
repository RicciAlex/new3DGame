//=============================================================================
//
// timer.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "timer.h"
#include "UIString.h"
#include <string>


//�R���X�g���N�^
CTimer::CTimer()
{
	//�����o�[�ϐ����N���A����
	m_fCurrentTime = 0.0f;
	m_fStartTime = 0.0f;
	m_fAddedTime = 0.0f;

	m_pString = nullptr;
}

//�f�X�g���N�^
CTimer::~CTimer()
{

}

//����������
HRESULT CTimer::Init(void)
{
	//�����o�[�ϐ�������������
	m_fStartTime = (float)timeGetTime();
	m_fCurrentTime = (float)timeGetTime();
	m_fAddedTime = 0.0f;

	m_pString = nullptr;

	return S_OK;
}

//�I������
void CTimer::Uninit(void)
{
	//UI�̔j������
	if (m_pString)
	{//null�`�F�b�N

		m_pString->Release();		//���������������
		m_pString = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CTimer::Update(void)
{
	m_fCurrentTime = (float)timeGetTime();

	int min = 0, sec = 0;

	float fTime = (float)(m_fCurrentTime - m_fStartTime) + m_fAddedTime;

	sec = (int)(fTime / 1000.0f) % 60;
	min = (int)(fTime / (60.0f * 1000.0f));

	if (m_pString)
	{
		std::string M = std::to_string(min);
		std::string S = std::to_string(sec);

		if (M.size() == 1)
		{
			M = "000" + std::to_string(min);
		}
		else if (M.size() == 2)
		{
			M = "00" + std::to_string(min);
		}
		else if (M.size() == 3)
		{
			M = "0" + std::to_string(min);
		}

		if (S.size() == 1)
		{
			S = "0" + std::to_string(sec);
		}

		std::string str = M + ":" + S;

		m_pString->ChangeString(str.c_str());
	}
}

//�`�揈��
void CTimer::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CTimer::SetPos(const D3DXVECTOR3 pos)
{

}

//���Ԃ̒ǉ�����
void CTimer::AddTime(const float fMilliseconds)
{
	m_fAddedTime += fMilliseconds;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CTimer::GetPos(void)
{
	return Vec3Null;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================




//��������
CTimer * CTimer::Create(void)
{
	CTimer* pTimer = new CTimer;			//�C���X�^���X�𐶐�����

	if (FAILED(pTimer->Init()))
	{//����������

		return nullptr;
	}

	pTimer->m_pString = CUIString::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f), D3DXVECTOR2(210.0f, 30.0f), ColorGreen, "0000:00");

	return pTimer;
}
