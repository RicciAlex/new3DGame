//=============================================================================
//
// starUI.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "starUI.h"
#include "object2D.h"
#include "UIString.h"
#include <string>

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CStarUI::DEFAULT_STAR_POS = D3DXVECTOR3(100.0f, 40.0f, 0.0f);			//�f�B�t�H���g�̉摜�̈ʒu
const D3DXVECTOR2 CStarUI::DEFAULT_STAR_SIZE = D3DXVECTOR2(30.0f, 30.0f);				//�f�B�t�H���g�̉摜�̃T�C�Y
const D3DXVECTOR3 CStarUI::DEFAULT_STRING_POS = D3DXVECTOR3(160.0f, 40.0f, 0.0f);		//�f�B�t�H���g�̈ʒu
const D3DXVECTOR2 CStarUI::DEFAULT_STRING_SIZE = D3DXVECTOR2(180.0f, 25.0f);			//�f�B�t�H���g�̃T�C�Y
const D3DXCOLOR	  CStarUI::DEFAULT_STRING_COLOR = D3DXCOLOR(1.0f, 0.9f, 0.0f, 1.0f);	//�f�B�t�H���g�̐F


//�R���X�g���N�^
CStarUI::CStarUI()
{
	//�����o�[�ϐ����N���A����
	m_nStarNumber = 0;
	m_nTargetStar = 0;
	m_bDone = false;

	m_pStar = nullptr;
	m_pString = nullptr;
}

//�f�X�g���N�^
CStarUI::~CStarUI()
{

}

//����������
HRESULT CStarUI::Init(void)
{
	//�����o�[�ϐ�������������
	m_nStarNumber = 0;
	m_nTargetStar = 0;
	m_bDone = false;

	m_pStar = nullptr;
	m_pString = nullptr;

	return S_OK;
}

//�I������
void CStarUI::Uninit(void)
{
	//2D�I�u�W�F�N�g�̔j������
	if (m_pStar)
	{//null�`�F�b�N

		m_pStar->Release();			//���������������
		m_pStar = nullptr;			//�|�C���^��null�ɂ���
	}

	//�����̔j������
	if (m_pString)
	{//null�`�F�b�N

		m_pString->Release();			//���������������
		m_pString = nullptr;			//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CStarUI::Update(void)
{
	
}

//�`�揈��
void CStarUI::Draw(void)
{

}

//����1�����Z���鏈��
void CStarUI::AddStar(void)
{
	if (!m_bDone)
	{
		m_nStarNumber++;

		if (m_pString)
		{
			if (m_nStarNumber < 10)
			{
				std::string str = "0" + std::to_string(m_nStarNumber) + "/" + std::to_string(m_nTargetStar);
				m_pString->ChangeString(str.c_str());
			}
			else
			{
				std::string str = std::to_string(m_nStarNumber) + "/" + std::to_string(m_nTargetStar);
				m_pString->ChangeString(str.c_str());
			}
		}

		if (m_nStarNumber == m_nTargetStar)
		{
			m_pString->ChangeString("DONE!");
			m_bDone = true;
		}
	}
}


//�ʒu�̐ݒ菈��
void CStarUI::SetPos(const D3DXVECTOR3 pos)
{

}

//�ړI�̐����̐ݒ菈��
void CStarUI::SetTargetStar(const int target)
{
	m_nTargetStar = target;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CStarUI::GetPos(void)
{
	return Vec3Null;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CStarUI* CStarUI::Create(const int nMaxStar)
{
	CStarUI* pUI = new CStarUI;			//�C���X�^���X�𐶐�����

	if (FAILED(pUI->Init()))
	{//����������
		return nullptr;
	}

	pUI->m_nTargetStar = nMaxStar;		//�ړI�̐����̐ݒ�

	//2D�I�u�W�F�N�g�̐���
	pUI->m_pStar = CObject_2D::Create();

	if (pUI->m_pStar)
	{//�����o������A�K�v�ȃp�����[�^��ݒ肷��

		pUI->m_pStar->SetPos( D3DXVECTOR3(100.0f, 40.0f, 0.0f));
		pUI->m_pStar->SetSize(D3DXVECTOR2(30.0f, 30.0f));
		pUI->m_pStar->SetTexture(CObject::TEXTURE_STAR_UI);
		pUI->m_pStar->SetPriority(4);
	}

	std::string str = "00/" + std::to_string(nMaxStar);

	pUI->m_pString = CUIString::Create(DEFAULT_STRING_POS, DEFAULT_STRING_SIZE, DEFAULT_STRING_COLOR, str.c_str());

	return pUI;
}