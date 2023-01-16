//=============================================================================
//
// cameraSetter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "cameraSetter.h"
#include "application.h"
#include "game.h"

#include "line.h"

//�R���X�g���N�^
CCameraSetter::CCameraSetter()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_size = Vec3Null;
	m_CameraTarget = (CPlayer::CAMERA_POS)0;
	m_bActive = false;
}

//�f�X�g���N�^
CCameraSetter::~CCameraSetter()
{

}

//����������
HRESULT CCameraSetter::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;
	m_size = Vec3Null;
	m_CameraTarget = CPlayer::CAMERA_POS_NORMAL;
	m_bActive = false;


	return S_OK;
}

//�I������
void CCameraSetter::Uninit(void)
{
	
}

//�X�V����
void CCameraSetter::Update(void)
{
	TestOverlap();
}

//�`�揈��
void CCameraSetter::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CCameraSetter::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CCameraSetter::GetPos(void)
{
	return m_pos;
}


//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================


//��������
CCameraSetter* CCameraSetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CPlayer::CAMERA_POS target)
{
	CCameraSetter* pSetter = new CCameraSetter;			//�C���X�^���X�𐶐�����

	if (FAILED(pSetter->Init()))
	{//����������
		return nullptr;
	}

	pSetter->m_pos = pos;					//�ʒu�̐ݒ�
	pSetter->m_size = size;					//�T�C�Y�̐ݒ�
	pSetter->m_CameraTarget = target;		//�J�����̖ړI�̈ʒu�̐ݒ�

#ifdef _DEBUG

											//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 VtxPos[8] = {};

	//���_���W�̐ݒ�
	VtxPos[0] = D3DXVECTOR3(- size.x * 0.5f, - size.y * 0.5f, + size.z * 0.5f);
	VtxPos[1] = D3DXVECTOR3(+ size.x * 0.5f, - size.y * 0.5f, + size.z * 0.5f);
	VtxPos[2] = D3DXVECTOR3(+ size.x * 0.5f, - size.y * 0.5f, - size.z * 0.5f);
	VtxPos[3] = D3DXVECTOR3(- size.x * 0.5f, - size.y * 0.5f, - size.z * 0.5f);
	VtxPos[4] = D3DXVECTOR3(- size.x * 0.5f, + size.y * 0.5f, + size.z * 0.5f);
	VtxPos[5] = D3DXVECTOR3(+ size.x * 0.5f, + size.y * 0.5f, + size.z * 0.5f);
	VtxPos[6] = D3DXVECTOR3(+ size.x * 0.5f, + size.y * 0.5f, - size.z * 0.5f);
	VtxPos[7] = D3DXVECTOR3(- size.x * 0.5f, + size.y * 0.5f, - size.z * 0.5f);

	//���̐���
	CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[2], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[3], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	CLine::Create(pos, Vec3Null, VtxPos[4], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[5], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[6], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[7], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !DEBUG

	return pSetter;					//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================



//�v���C���[�Əd�Ȃ��Ă��邩�ǂ���
bool CCameraSetter::TestOverlap(void)
{
	CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();

	if (pPlayer)
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		if (playerPos.x >= m_pos.x - (m_size.x * 0.5f) && playerPos.x <= m_pos.x + (m_size.x * 0.5f) &&
			playerPos.y >= m_pos.y - (m_size.y * 0.5f) && playerPos.y <= m_pos.y + (m_size.y * 0.5f) &&
			playerPos.z >= m_pos.z - (m_size.z * 0.5f) && playerPos.z <= m_pos.z + (m_size.z * 0.5f))
		{
 			pPlayer->SetTargetCameraPos(m_CameraTarget);

			m_bActive = true;

			return true;
		}
	}

	if (m_bActive)
	{
		pPlayer->SetTargetCameraPos(CPlayer::CAMERA_POS_NORMAL);

		m_bActive = false;
	}

	return false;
}
