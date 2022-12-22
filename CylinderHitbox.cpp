//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "CylinderHitbox.h"
#include "line.h"

//�R���X�g���N�^
CCylinderHitbox::CCylinderHitbox()
{
	//�����o�[�ϐ����N���A����

	//�f�o�b�O�p�̐�
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CCylinderHitbox::~CCylinderHitbox()
{

}

//����������
HRESULT CCylinderHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�f�o�b�O�p�̐�
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CCylinderHitbox::Uninit(void)
{
	//�f�o�b�O�p�̐��̔j��
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->Release();
			m_pLine[nCnt] = nullptr;
		}
	}

	//��{�N���X�̏I������
	CHitbox::Uninit();
}

//�X�V����
void CCylinderHitbox::Update(void)
{
	if (GetType() == TYPE_PLAYER)
	{//�v���C���[�̃q�b�g�{�b�N�X��������A
		std::vector <CHitbox*>* pHbx = GetAllHitbox();			//�S���̃q�b�g�{�b�N�X���擾����
		SetCollisionDirection(NO_COLLISION);
		SetScore(0);
		SetDirection(Vec3Null);

		for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
		{//�擾�����q�b�g�{�b�N�X��S�����肷��

			if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent() && GetOverlapResponse(pHbx->data()[nCnt]->GetType()) != RESPONSE_IGNORE)
			{//�e�������ł͂Ȃ�������

				HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();			//�`�̎擾

				switch (shape)
				{
				case CHitbox::SHAPE_SPHERE:
					break;

				case CHitbox::SHAPE_BOX:

				{//��`�̏ꍇ

					if (PointBoxHit(pHbx->data()[nCnt]) != CHitbox::NO_COLLISION)
					{//���������ꍇ

						if (pHbx->data()[nCnt]->GetType() != TYPE_OBSTACLE || !GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir;

								D3DXVECTOR3 dirP, dirO;

								dirP = GetPos() - GetLastPos();
								dirO = pHbx->data()[nCnt]->GetPos() - pHbx->data()[nCnt]->GetLastPos();

								if (D3DXVec3Length(&dirP) > 0.0f && D3DXVec3Length(&dirO) > 0.0f)
								{
									dir = dirO - dirP;
								}
								else if (D3DXVec3Length(&dirP) > 0.0f)
								{
									dir = -dirP;
								}
								else if (D3DXVec3Length(&dirO) > 0.0f)
								{
									dir = dirO;
								}
								else
								{
									dir = D3DXVECTOR3((float)CObject::random(-1000, 1000), (float)CObject::random(-1000, 1000), (float)CObject::random(-1000, 1000));
								}

								D3DXVec3Normalize(&dir, &dir);
								pHbx->data()[nCnt]->SetDirection(dir);
							}
							if (pHbx->data()[nCnt]->GetScore() != 0)
							{
								SetScore(pHbx->data()[nCnt]->GetScore());
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}

						if (pHbx->data()[nCnt]->GetMove() != Vec3Null)
						{
							SetMove(GetMove() + pHbx->data()[nCnt]->GetMove());
						}
						if (pHbx->data()[nCnt]->GetAcceleration() != Vec3Null)
						{
							SetAcceleration(GetAcceleration() + pHbx->data()[nCnt]->GetAcceleration());
						}
					}
				}

				break;

				case CHitbox::SHAPE_CYLINDER:

				{//�V�����_�[�̏ꍇ

					if (CylinderCylinderHit(pHbx->data()[nCnt]) != CHitbox::NO_COLLISION)
					{//���������ꍇ

						if (pHbx->data()[nCnt]->GetType() != TYPE_OBSTACLE || !GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							pHbx->data()[nCnt]->SetCollisionState(true);		//����������Ԃɂ���

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				default:
					break;
				}
			}
		}
	}

	//�f�o�b�O�p�̐��̍X�V
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->SetPos(GetPos());
		}
	}

	//��{�N���X�̍X�V
	CHitbox::Update();
}


//=============================================================================
//
//							�ÓI�֐�
//
//=============================================================================

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;
}

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nPlayerIdx)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;		//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetPlayerIdx(nPlayerIdx);					//�v���C���[�C���f�b�N�X�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;					//���������C���X�^���X��Ԃ�
}

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;						//���������C���X�^���X��Ԃ�
}

CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�
	pHitbox->SetEffect(effect);							//�G�t�F�N�g�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;					//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//						�@�@�@�@�v���C�x�[�g�֐�
//
//=============================================================================



//�V�����_�[�ƃV�����_�[�̓����蔻��
CCylinderHitbox::COLLISION_DIRECTION CCylinderHitbox::CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos, thisSize;				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	thisPos = GetPos();							//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	thisSize = GetSize();						//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	float fTop, fBottom;				//���̃q�b�g�{�b�N�X�̏㑤�Ɖ���

	fTop = pos.y + size.y;				//�㑤�̍��W
	fBottom = pos.y;					//�����̍��W

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//Y���W���d�Ȃ����ꍇ

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//����
		fRadius = size.x + thisSize.x;				//���a�̑����Z

		if (fDistance < fRadius)
		{//�����͔��a�̑����Z��菬����������

			D3DXVECTOR3 thisLast = GetLastPos();					//�O��̈ʒu�̎擾
			D3DXVECTOR3 parentPos = GetParent()->GetPos();			//�e�̎擾

			if (thisLast.y + thisSize.y <= pos.y)
			{//�����瓖�������ꍇ
				thisPos.y = (pos.y - thisSize.y - 0.01f);		//�V�����ʒu�̌v�Z
				parentPos = thisPos - GetRelativePos();			
				GetParent()->SetPos(parentPos);					//�e�������o��
				SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
				SetCollisionDirection(FROM_BELOW);

				return FROM_BELOW;
			}
			else if (thisLast.y >= pos.y + size.y)
			{//�ォ�瓖�������ꍇ
				thisPos.y = (pos.y + size.y + 0.01f);			//�V�����ʒu�̌v�Z
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);					//�e�������o��
				SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
				SetCollisionDirection(FROM_ABOVE);

				return FROM_ABOVE;
			}
			else
			{//�����瓖�������ꍇ
				D3DXVECTOR3 dist = thisPos - pos;					//�������v�Z����
				float fHeight = parentPos.y;						//���݂̍���
				dist.y = 0.0f;										
				D3DXVec3Normalize(&dist, &dist);					//�����𐳋K������
				dist.x *= fRadius + 0.001f;							
				dist.z *= fRadius + 0.001f;							
				dist.x += pos.x;									
				dist.z += pos.z;									
				parentPos = dist - GetRelativePos();				//�V�����ʒu���v�Z����
				parentPos.y = fHeight;								//���̍�����ݒ肷��
				GetParent()->SetPos(parentPos);						//�e�̈ʒu�̐ݒ�

				return FROM_SIDE;				//true��Ԃ�
			}
		}
	}

	return NO_COLLISION;						//false��Ԃ�
}

//�V�����_�[�ƃV�����_�[�̓����蔻��
CCylinderHitbox::COLLISION_DIRECTION CCylinderHitbox::CylinderCylinderHit(CHitbox* pOther)
{
	D3DXVECTOR3 pos = pOther->GetPos(), size = pOther->GetSize();		//���̃I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾����
	D3DXVECTOR3 thisPos, thisSize;				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	thisPos = GetPos();							//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	thisSize = GetSize();						//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	float fTop, fBottom;				//���̃q�b�g�{�b�N�X�̏㑤�Ɖ���

	fTop = pos.y + size.y;				//�㑤�̍��W
	fBottom = pos.y;					//�����̍��W

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//Y���W���d�Ȃ����ꍇ

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//����
		fRadius = size.x + thisSize.x;				//���a�̑����Z

		if (fDistance < fRadius)
		{//�����͔��a�̑����Z��菬����������

			D3DXVECTOR3 thisLast = GetLastPos();					//�O��̈ʒu�̎擾
			D3DXVECTOR3 parentPos = GetParent()->GetPos();			//�e�̎擾

			if (thisLast.y + thisSize.y <= pos.y)
			{//�����瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					thisPos.y = (pos.y - thisSize.y - 0.01f);		//�V�����ʒu�̌v�Z
					parentPos = thisPos - GetRelativePos();
					GetParent()->SetPos(parentPos);					//�e�������o��
					SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
					SetCollisionDirection(FROM_BELOW);
				}

				return FROM_BELOW;
			}
			else if (thisLast.y >= pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					thisPos.y = (pos.y + size.y + 0.01f);			//�V�����ʒu�̌v�Z
					parentPos = thisPos - GetRelativePos();
					GetParent()->SetPos(parentPos);					//�e�������o��
					SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
					SetCollisionDirection(FROM_ABOVE);
				}

				return FROM_ABOVE;
			}
			else
			{//�����瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					D3DXVECTOR3 dist = thisPos - pos;					//�������v�Z����
					float fHeight = parentPos.y;						//���݂̍���
					dist.y = 0.0f;
					D3DXVec3Normalize(&dist, &dist);					//�����𐳋K������
					dist.x *= fRadius + 0.001f;
					dist.z *= fRadius + 0.001f;
					dist.x += pos.x;
					dist.z += pos.z;
					parentPos = dist - GetRelativePos();				//�V�����ʒu���v�Z����
					parentPos.y = fHeight;								//���̍�����ݒ肷��
					GetParent()->SetPos(parentPos);						//�e�̈ʒu�̐ݒ�
				}

				return FROM_SIDE;				//true��Ԃ�
			}
		}
	}

	return NO_COLLISION;						//false��Ԃ�
}


//�_�Ƌ�`�̓����蔻��
CCylinderHitbox::COLLISION_DIRECTION CCylinderHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	D3DXVECTOR3 thisSize = GetSize();					//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	D3DXVECTOR3 thisLastPos = GetLastPos();				//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y���W���d�Ȃ����ꍇ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//�v�Z�p�̃x�N�g��
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//�v�Z�p�̃}�g���b�N�X
		float fResult;											//�v�Z�p�̕ϐ�

		//���_�̑��΍��W�̐ݒ�
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//���΍��W�����΍��W�ɕϊ�����
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//�e���_���玟�̒��_�܂ł̃x�N�g�����v�Z����
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//�e���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g�����v�Z����
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//��̃x�N�g���̊O�ς��v�Z����
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//�S���̊O�ς̕�����������������A���������Ƃ����Ӗ��ł�

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				//�V�����ʒu�̌v�Z
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�

				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
				SetCollisionDirection(FROM_ABOVE);

				return FROM_ABOVE;			//true��Ԃ�
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//�����瓖�������ꍇ

				 //�V�����ʒu�̌v�Z
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
				SetCollisionDirection(FROM_BELOW);

				return FROM_BELOW;			//true��Ԃ�
			}
			else
			{//�����瓖�������ꍇ

				for (int Count = 0; Count < 4; Count++)
				{
					//�ǂ����瓖�����������߂�

					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//�ǂ����瓖������������������

						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g��
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//�O��̈ʒu���璸�_�܂ł̃x�N�g��
						D3DXVec3Normalize(&N, &P[0]);			//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g���𐳋K������

						//��̃x�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O�ς��v�Z����
						D3DXVec3Cross(&R[0], &P[1], &V[Count]);
						D3DXVec3Cross(&R[1], &N, &V[Count]);

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;

						if (fResult > 0)
						{
							fResult -= 0.001f;
						}
						else if (fResult < 0)
						{
							fResult += 0.001f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;
						float Dot, Lenght1, Lenght2, Alpha;

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//��_���W
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g��
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//���_�����_�܂ł̃x�N�g��

						D3DXVec3Normalize(&N, &VtxtoCross);			//���_�����_�܂ł̃x�N�g���𐳋K������

						//���_�����_�܂ł̃x�N�g���ƒ��_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g���̓��ς��v�Z����
						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//��̃x�N�g���̒������v�Z����
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//��̃x�N�g���̒������v�Z����

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{//���
							//�V�����ʒu���v�Z����
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));

							fResult = (Lenght2 * cosf(Alpha));

							//�V�����ʒu�̐ݒ�
							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{//�G���[����������A�V�����ʒu����_���W�ɐݒ肷��

							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				SetPos(thisPos);										//���݂̈ʒu�̐ݒ�

				return FROM_SIDE;			//true��Ԃ�
			}
		}
	}

	return NO_COLLISION;						//false��Ԃ�
}

//�_�Ƌ�`�̓����蔻��
CCylinderHitbox::COLLISION_DIRECTION CCylinderHitbox::PointBoxHit(CHitbox* pOther)
{
	D3DXVECTOR3 pos = pOther->GetPos(), rot = pOther->GetRot(), size = pOther->GetSize();		//���̃I�u�W�F�N�g�̈ʒu�A��]�ƃT�C�Y���擾����
	D3DXVECTOR3 thisPos = GetPos();						//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	D3DXVECTOR3 thisSize = GetSize();					//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	D3DXVECTOR3 thisLastPos = GetLastPos();				//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y���W���d�Ȃ����ꍇ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//�v�Z�p�̃x�N�g��
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//�v�Z�p�̃}�g���b�N�X
		float fResult;											//�v�Z�p�̕ϐ�

																//���_�̑��΍��W�̐ݒ�
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//���΍��W�����΍��W�ɕϊ�����
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//�e���_���玟�̒��_�܂ł̃x�N�g�����v�Z����
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//�e���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g�����v�Z����
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//��̃x�N�g���̊O�ς��v�Z����
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//�S���̊O�ς̕�����������������A���������Ƃ����Ӗ��ł�

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					//�V�����ʒu�̌v�Z
					thisPos.y = pos.y + size.y + 0.01f;
					SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�

					GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
					SetCollisionDirection(FROM_ABOVE);
				}

				return FROM_ABOVE;			//true��Ԃ�
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//�����瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					//�V�����ʒu�̌v�Z
					thisPos.y = pos.y - thisSize.y - 0.01f;

					SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
					GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
					SetCollisionDirection(FROM_BELOW);
				}

				return FROM_BELOW;			//true��Ԃ�
			}
			else
			{//�����瓖�������ꍇ

				if (GetOverlapResponse(pOther->GetType()) == RESPONSE_EXTRUDE)
				{
					for (int Count = 0; Count < 4; Count++)
					{
						//�ǂ����瓖�����������߂�

						PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
						D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

						D3DXVECTOR3 Ctrl;

						if (RCtrl.y * R[Count].y <= 0)
						{//�ǂ����瓖������������������

							P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g��
							P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//�O��̈ʒu���璸�_�܂ł̃x�N�g��
							D3DXVec3Normalize(&N, &P[0]);			//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g���𐳋K������

																	//��̃x�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O�ς��v�Z����
							D3DXVec3Cross(&R[0], &P[1], &V[Count]);
							D3DXVec3Cross(&R[1], &N, &V[Count]);

							if (R[1].y == 0)
							{
								break;
							}

							fResult = R[0].y / R[1].y;

							if (fResult > 0)
							{
								fResult -= 0.001f;
							}
							else if (fResult < 0)
							{
								fResult += 0.001f;
							}

							D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;
							float Dot, Lenght1, Lenght2, Alpha;

							Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//��_���W
							VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g��
							VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//���_�����_�܂ł̃x�N�g��

							D3DXVec3Normalize(&N, &VtxtoCross);			//���_�����_�܂ł̃x�N�g���𐳋K������

																		//���_�����_�܂ł̃x�N�g���ƒ��_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g���̓��ς��v�Z����
							Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
							Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//��̃x�N�g���̒������v�Z����
							Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//��̃x�N�g���̒������v�Z����

							if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
							{//���
							 //�V�����ʒu���v�Z����
								Alpha = acosf((Dot) / (Lenght1 * Lenght2));

								fResult = (Lenght2 * cosf(Alpha));

								//�V�����ʒu�̐ݒ�
								thisPos.x = Vtx[Count].x + (N.x * (fResult));
								thisPos.z = Vtx[Count].z + (N.z * (fResult));
							}
							else
							{//�G���[����������A�V�����ʒu����_���W�ɐݒ肷��

								thisPos.x = thisLastPos.x + (N.x * fResult);
								thisPos.z = thisLastPos.z + (N.z * fResult);
							}

							break;
						}
					}

					GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
					SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
					SetPos(thisPos);										//���݂̈ʒu�̐ݒ�
				}

				return FROM_SIDE;			//true��Ԃ�
			}
		}
	}

	return NO_COLLISION;						//false��Ԃ�
}