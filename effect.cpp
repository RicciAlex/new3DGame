//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CEffect::CEffect()
{
	//�����o�[�ϐ����N���A����
	m_nLife = 0;
	m_move = Vec3Null;
}

//�f�X�g���N�^
CEffect::~CEffect()
{

}

//����������
HRESULT CEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBillboard::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_nLife = DEFAULT_LIFE;
	m_move = Vec3Null;

	return S_OK;
}

//�I������
void CEffect::Uninit(void)
{
	//��{�N���X�̏I������
	CBillboard::Uninit();
}

//�X�V����
void CEffect::Update(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		Release();
		return;
	}

	if (D3DXVec3Length(&m_move) > 0.0f)
	{
		SetPos(GetPos() + m_move);
	}

	//��{�N���X�̍X�V����
	CBillboard::Update();
}

//�`�揈��
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	
	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//��{�N���X�̕`�揈��
	CBillboard::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//���x�̐ݒ菈��
void CEffect::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//���C�t�̐ݒ菈��
void CEffect::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//���x�̎擾����
const D3DXVECTOR3 CEffect::GetMove(void)
{
	return m_move;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================


//��������
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col)
{
	CEffect* pEffect = new CEffect;		//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetSize(size);				//�T�C�Y�̐ݒ�
	pEffect->SetColor(col);				//�F�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}

//��������
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife)
{
	CEffect* pEffect = new CEffect;		//�C���X�^���X�𐶐�����

										//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetSize(size);				//�T�C�Y�̐ݒ�
	pEffect->SetColor(col);				//�F�̐ݒ�
	pEffect->m_nLife = nLife;			//���C�t�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}

//��������
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const D3DXVECTOR3 move)
{
	CEffect* pEffect = new CEffect;		//�C���X�^���X�𐶐�����

										//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetSize(size);				//�T�C�Y�̐ݒ�
	pEffect->SetColor(col);				//�F�̐ݒ�
	pEffect->m_move = move;				//���x�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}

//��������
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife, const D3DXVECTOR3 move)
{
	CEffect* pEffect = new CEffect;		//�C���X�^���X�𐶐�����

										//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetSize(size);				//�T�C�Y�̐ݒ�
	pEffect->SetColor(col);				//�F�̐ݒ�
	pEffect->m_nLife = nLife;			//���C�t�̐ݒ�
	pEffect->m_move = move;				//���x�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}