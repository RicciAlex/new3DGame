//=============================================================================
//
// accelerationFloor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "accelerationFloor.h"
#include "BoxHitbox.h"
#include "application.h"
#include "game.h"
#include "player.h"


//�R���X�g���N�^
CAccelerationFloor::CAccelerationFloor()
{
	//�����o�[�ϐ����N���A����
	m_bActive = false;
	m_speed = Vec2Null;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CAccelerationFloor::~CAccelerationFloor()
{

}

//����������
HRESULT CAccelerationFloor::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_bActive = true;
	m_speed = Vec2Null;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CAccelerationFloor::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CObject_3D::Uninit();
}

//�X�V����
void CAccelerationFloor::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_3D::Update();
}

//���x�̐ݒ菈��
void CAccelerationFloor::SetSpeed(const D3DXVECTOR2 speed)
{
	m_speed = speed;
}

//���x�̐ݒ菈��
void CAccelerationFloor::SetSpeed(const float speedX, const float speedY)
{
	m_speed = D3DXVECTOR2(speedX, speedY);

	D3DXVECTOR2 tiling = GetTextureTiling();

	MoveTexCoordinates(D3DXVECTOR2(m_speed.x * -0.01f * tiling.x, m_speed.y * 0.01f * tiling.y));
}

//�e�N�X�`���̈ړ��ʂ̐ݒ菈��
void CAccelerationFloor::SetTextureTiling(const D3DXVECTOR2 tiling)
{
	D3DXVECTOR2 spd = m_speed;
	D3DXVec2Normalize(&spd, &spd);
	CObject_3D::SetTextureTiling(tiling);
	MoveTexCoordinates(D3DXVECTOR2(spd.x * -0.01f * tiling.x, spd.y * 0.01f * tiling.y));
}

//�e�N�X�`���̑傫���̐ݒ菈��
void CAccelerationFloor::SetTextureTiling(const float fTiling)
{
	D3DXVECTOR2 spd = m_speed;
	D3DXVec2Normalize(&spd, &spd);
	CObject_3D::SetTextureTiling(fTiling);
	MoveTexCoordinates(D3DXVECTOR2(spd.x * -0.01f * fTiling, spd.y * 0.01f * fTiling));
}

//�e�N�X�`���̑傫���̐ݒ菈��
void CAccelerationFloor::SetTextureTiling(const float fTilingX, const float fTilingY)
{
	D3DXVECTOR2 spd = m_speed;
	D3DXVec2Normalize(&spd, &spd);
	CObject_3D::SetTextureTiling(fTilingX, fTilingY);
	MoveTexCoordinates(D3DXVECTOR2(spd.x * -0.01f * fTilingX, spd.y * 0.01f * fTilingY));
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CAccelerationFloor* CAccelerationFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed)
{
	CAccelerationFloor* pFloor = new CAccelerationFloor;		//�C���X�^���X�𐶐�����

	if (FAILED(pFloor->Init()))
	{//����������
		return nullptr;
	}

	pFloor->SetPos(pos);
	pFloor->SetSize(size);
	pFloor->m_bActive = true;
	pFloor->m_speed = speed;
	pFloor->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	D3DXVECTOR2 spd = speed;
	D3DXVec2Normalize(&spd, &spd);
	pFloor->MoveTexCoordinates(D3DXVECTOR2(spd.x * -0.01f, spd.y * 0.01f));

	if (speed.x > 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_RIGHT);
	}
	else if(speed.x < 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_LEFT);
	}
	else if (speed.y > 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_UP);
	}
	else if (speed.y < 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_DOWN);
	}

	pFloor->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), D3DXVECTOR3(size.x, 10.0f, size.y), CHitbox::TYPE_OVERLAPPABLE, pFloor);

	if (pFloor->m_pHitbox)
	{
		pFloor->m_pHitbox->SetAcceleration(D3DXVECTOR3(speed.x, 0.0f, speed.y));
		pFloor->m_pHitbox->IgnoreAllCollision();
		pFloor->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);
	}

	return pFloor;
}

//��������
CAccelerationFloor * CAccelerationFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed, CObject::TextType texture)
{
	CAccelerationFloor* pFloor = new CAccelerationFloor;		//�C���X�^���X�𐶐�����

	if (FAILED(pFloor->Init()))
	{//����������
		return nullptr;
	}

	pFloor->SetPos(pos);
	pFloor->SetSize(size);
	pFloor->m_bActive = true;
	pFloor->m_speed = speed;
	pFloor->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	D3DXVECTOR2 spd = speed;
	D3DXVec2Normalize(&spd, &spd);
	pFloor->MoveTexCoordinates(D3DXVECTOR2(spd.x * -0.01f, spd.y * 0.01f));
	pFloor->SetTexture(texture);

	pFloor->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), D3DXVECTOR3(size.x, 10.0f, size.y), CHitbox::TYPE_OVERLAPPABLE, pFloor);

	if (pFloor->m_pHitbox)
	{
		pFloor->m_pHitbox->SetAcceleration(D3DXVECTOR3(speed.x, 0.0f, speed.y));
		pFloor->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);
	}

	return pFloor;
}
