//=============================================================================
//
// menu.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "menu.h"
#include "object2D.h"


//�R���X�g���N�^
CMenu::CMenu()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;

	m_pBg = nullptr;
}

//�f�X�g���N�^
CMenu::~CMenu()
{

}

//����������
HRESULT CMenu::Init(void)
{
	//�����o�[�ϐ�������������

	m_pos = Vec3Null;

	m_pBg = nullptr;

	return S_OK;
}

//�I������
void CMenu::Uninit(void)
{
	//�w�i�̔j������
	if (m_pBg)
	{//null�`�F�b�N

		m_pBg->Release();		//���������������
		m_pBg = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CMenu::Update(void)
{
	if (m_pBg)
	{
		m_pBg->Update();
	}
}

//�`�揈��
void CMenu::Draw(void)
{
	
}

//�ʒu�̐ݒ菈��
void CMenu::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pBg)
	{
		m_pBg->SetPos(pos);
	}
}

//�ʒu�̎擾����
const D3DXVECTOR3 CMenu::GetPos(void)
{
	return m_pos;
}

//�w�i��������
void CMenu::CreateBg(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, CObject::TextType texture)
{
	if (!m_pBg)
	{//null�`�F�b�N

		m_pBg = CObject_2D::Create();			//�w�i�𐶐�����

		if (m_pBg)
		{//�����o������A�K�v�ȃp�����[�^��ݒ肷��

			m_pBg->SetPos(pos);
			m_pBg->SetSize(size);
			m_pBg->SetTexture(texture);
			m_pBg->SetPriority(5);
		}
	}
}

//�w�i�̎擾����
const CObject_2D * CMenu::GetBg(void)
{
	return m_pBg;
}
