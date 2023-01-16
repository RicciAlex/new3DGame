//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"
#include "rendering.h"
#include "CylinderHitbox.h"
#include "starUI.h"

#include "animationFade.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================

const D3DXVECTOR3 CPlayer::m_baseCameraPos = D3DXVECTOR3(0.0f, 250.0f, -400.0f);							//���ʂ̃J�����̈ʒu
const D3DXVECTOR3 CPlayer::m_baseFocalPointPos = D3DXVECTOR3(0.0f, 0.0f, 300.0f);						//���ʂ̒����_�̈ʒu
const D3DXVECTOR3 CPlayer::m_BackCameraPos = D3DXVECTOR3(0.0f, 250.0f, -550.0f);							//���̃J�����̈ʒu
const float CPlayer::m_MaxWalkingSpeed = 7.0f;			//�ő�����X�s�[�h
const float CPlayer::m_AccelerationCoeff = 8.0f;		//�����W��
const D3DXVECTOR3 CPlayer::m_playerSize = D3DXVECTOR3(30.0f, 175.0f, 30.0f);				//�v���C���[�̃T�C�Y

//�v���C���[�̐F
D3DXCOLOR CPlayer::m_playerColor[PLAYER_COLOR_MAX]
{

	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f }
};

//�R���X�g���N�^
CPlayer::CPlayer() : CObject::CObject(1)
{
	//�����o�[�ϐ����N���A����
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_pos = Vec3Null;								//�ʒu
	m_move = Vec3Null;								//���x�̏���������
	m_DestRot = Vec3Null;							//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_rot = Vec3Null;								//����
	m_bRot = false;									//��]�������ǂ���
	m_respawnPoint = Vec3Null;
	m_cameraPos = Vec3Null;							//�J�����̑��Έʒu
	m_cameraTarget = Vec3Null;						//�J�����̖ړI�̈ʒu
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_State = (STATE)0;								//�A�j���[�V�������
	m_bJump = false;								//�W�����v���Ă��邩�ǂ���
	m_bLanded = false;
	m_bMoving = false;								//�ړ����Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;						//���G��Ԃ̃J�E���^�[
	m_bAttacking = false;							//�U�����Ă��邩�ǂ���
	m_nCntAttack = 0;								//�U���J�E���^�[
	m_fFrictionCoeff = 0.0f;						//���C�W��
	m_bFall = false;								//�������Ă��邩�ǂ���
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X
	m_bMoveCamera = false;							//�J�����̈ʒu���X�V���邩�ǂ���
	m_bCameraAnim = false;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_pos = Vec3Null;								//�ʒu
	m_move = Vec3Null;								//���x�̏���������
	m_DestRot = Vec3Null;							//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		//����
	m_respawnPoint = Vec3Null;
	m_cameraPos = m_baseCameraPos;					//�J�����̑��Έʒu
	m_cameraTarget = m_baseCameraPos;				//�J�����̖ړI�̈ʒu
	m_bRot = false;									//��]�������ǂ���
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_State = STATE_NEUTRAL;						//�A�j���[�V�������
	m_bJump = false;								//�W�����v���Ă��邩�ǂ���
	m_bLanded = false;
	m_bMoving = false;								//�ړ����Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;						//���G��Ԃ̃J�E���^�[
	m_bAttacking = false;							//�U�����Ă��邩�ǂ���
	m_nCntAttack = 0;								//�U���J�E���^�[
	m_fFrictionCoeff = 0.1f;						//���C�W��
	m_bFall = false;								//�������Ă��邩�ǂ���
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X
	m_bMoveCamera = false;							//�J�����̈ʒu���X�V���邩�ǂ���
	m_bCameraAnim = false;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}

	m_pUI = CStarUI::Create(10);

	if (!m_pUI)
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	//�A�j���[�^�[�̔j������
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//UI�̔j������
	if (m_pUI != nullptr)
	{
		m_pUI->Release();
		m_pUI = nullptr;
	}
}

//�X�V����
void CPlayer::Update(void)
{
	if (!m_bCameraAnim)
	{
		TransformUpdate();

		FieldUpdate();

		if (m_nInvincibilityCnt > 0)
		{
			m_nInvincibilityCnt--;

			if (m_nInvincibilityCnt <= 0)
			{
				m_nInvincibilityCnt = 0;
				m_pHitbox->SetInvincibility(false);
			}
		}

		UpdateHitbox();

		UpdateAnimation();

		if (m_pos.y <= -1000.0f)
		{
			RespawnPlayer();
			m_bFall = false;
		}

		UpdatePlayerCamera();

		if (CInputKeyboard::GetKeyboardTrigger(DIK_U))
		{
			m_bCameraAnim = true;
			CAnimationFade::Create(D3DXVECTOR3(-1500.0f, -200.0f, 500.0f) + m_cameraPos, D3DXVECTOR3(-1500.0f, -200.0f, 500.0f) + m_baseFocalPointPos, CAnimationFade::TYPE_PLATFORM);
		}
	}

	/*if (CInputKeyboard::GetKeyboardTrigger(DIK_M))
	{
		SetTargetCameraPos(CAMERA_POS_BACK);
	}
	else if (CInputKeyboard::GetKeyboardTrigger(DIK_N))
	{
		SetTargetCameraPos(CAMERA_POS_NORMAL);
	}*/

	CDebugProc::Print("\n\n Pos: %f %f %f", m_pos.x, m_pos.y, m_pos.z);
}

//�`�揈��
void CPlayer::Draw(void)
{
	if (m_nInvincibilityCnt % 10 <= 5)
	{//���G��Ԃ�������A�_�ł�����

		D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
		D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		m_pModel[BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

		for (int nCnt = 1; nCnt < PARTS_MAX; nCnt++)
		{//���̃��f���̕`�揈��
			if (m_pModel[nCnt] != nullptr)
			{
				m_pModel[nCnt]->Draw();
			}
		}
	}
}

//��1�̉��Z����
void CPlayer::AddStar(void)
{
	if (m_pUI)
	{
		m_pUI->AddStar();
	}
}

//�ʒu�̐ݒ菈��
void CPlayer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�����̐ݒ菈��
void CPlayer::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//���n���Ă��邩�ǂ����̐ݒ菈��
void CPlayer::SetLanded(void)
{
	if (m_bJump)
	{
		if (m_pAnimator)
		{

			m_bJump = false;		//���n���Ă����Ԃɂ���
			m_bLanded = true;

			if (!m_bMoving)
			{
				m_pAnimator->SetPresentAnim(CPlayer::STATE_NEUTRAL);
			}
			else
			{
				m_pAnimator->SetPresentAnim(CPlayer::STATE_RUNNING);
			}
		}
	}
}

//���x�̐ݒ菈��
void CPlayer::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�J�����̖ړI�̈ʒu�̐ݒ菈��
void CPlayer::SetTargetCameraPos(CAMERA_POS pos)
{
	switch (pos)
	{
	case CPlayer::CAMERA_POS_NORMAL:

	{
		m_cameraTarget = m_baseCameraPos;
	}

		break;

	case CPlayer::CAMERA_POS_BACK:

	{
		m_cameraTarget = m_BackCameraPos;
	}

		break;

	default:
		break;
	}

	m_bMoveCamera = true;
}

//���X�|�[���̈ʒu�̐ݒ菈��
void CPlayer::SetRespawnPoint(const D3DXVECTOR3 pos)
{
	m_respawnPoint = pos;
}

//�J�����A�j���[�V�����̐ݒ菈��
void CPlayer::SetCameraAnim(const bool bAnim)
{
	m_bCameraAnim = bAnim;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//�O��̈ʒu�̎擾����
const D3DXVECTOR3 CPlayer::GetLastPos(void)
{
	return m_LastPos;
}

//���x�̎擾����
const D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================

//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, int nCntPlayer)
{
	CPlayer* pModel = new CPlayer;		//�C���X�^���X�𐶐�����

	//�v���C���[�̏���������
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;						//�ʒu�̐ݒ�
	pModel->m_LastPos = pos;					//�O��̈ʒu�̐ݒ�
	pModel->m_respawnPoint = pos;				//���X�|�[���̈ʒu�̐ݒ�

	pModel->m_rot = D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f);
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_PLAYER_BODY, D3DXVECTOR3(0.0f, 53.0f, 0.0f), D3DXVECTOR3(0.0f, -2.98f, 0.0f));				//�̂̃��f���𐶐�����

	pModel->m_pModel[HEAD] = CModelPart::Create(CModel::MODEL_PLAYER_HEAD, D3DXVECTOR3(0.0f, 76.0f, 0.0f), D3DXVECTOR3(0.0f, -0.19f, 0.0f));							//���̃��f���𐶐�����
	pModel->m_pModel[HEAD]->SetParent(pModel->m_pModel[BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[LEFT_ARM] = CModelPart::Create(CModel::MODEL_PLAYER_FOREARM, D3DXVECTOR3(-14.0f, 63.0f, 0.0f), D3DXVECTOR3(-0.19f, -1.16f, -1.12f));		//���r�̃��f���𐶐�����
	pModel->m_pModel[LEFT_ARM]->SetParent(pModel->m_pModel[BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[LEFT_HAND] = CModelPart::Create(CModel::MODEL_PLAYER_ARM, D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXVECTOR3(2.07f, 0.75f, 0.062f));		//����̃��f���𐶐�����
	pModel->m_pModel[LEFT_HAND]->SetParent(pModel->m_pModel[LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_ARM] = CModelPart::Create(CModel::MODEL_PLAYER_FOREARM, D3DXVECTOR3(14.0f, 63.0f, 0.0f), D3DXVECTOR3(1.13f, 0.062f, 0.43f));	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[RIGHT_ARM]->SetParent(pModel->m_pModel[BODY]);															//�E�r�̐e��ݒ肷��

	pModel->m_pModel[RIGHT_HAND] = CModelPart::Create(CModel::MODEL_PLAYER_ARM, D3DXVECTOR3(-0.0f, -20.0f, 0.0f), D3DXVECTOR3(0.47f, -0.44f, -1.7f));	//�E��̃��f���𐶐�����
	pModel->m_pModel[RIGHT_HAND]->SetParent(pModel->m_pModel[RIGHT_ARM]);													//�E��̐e��ݒ肷��

	pModel->m_pModel[LEFT_LEG] = CModelPart::Create(CModel::MODEL_PLAYER_LEG, D3DXVECTOR3(8.0f, 10.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[LEFT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�����ڂ̐e��ݒ肷��

	pModel->m_pModel[LEFT_FOOT] = CModelPart::Create(CModel::MODEL_PLAYER_FOOT, D3DXVECTOR3(0.1f, -30.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[LEFT_FOOT]->SetParent(pModel->m_pModel[LEFT_LEG]);														//�����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_LEG] = CModelPart::Create(CModel::MODEL_PLAYER_LEG, D3DXVECTOR3(-8.0f, 10.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[RIGHT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_PLAYER_FOOT, D3DXVECTOR3(-0.1f, -30.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
	pModel->m_pModel[RIGHT_FOOT]->SetParent(pModel->m_pModel[RIGHT_LEG]);													//�E���̐e��ݒ肷��

	pModel->m_pModel[SAYA] = CModelPart::Create(CModel::MODEL_SAYA, D3DXVECTOR3(12.3f, 31.19f, -15.0f), D3DXVECTOR3(-2.2f, -2.95f, -1.46f));		//��̃��f���𐶐�����
	pModel->m_pModel[SAYA]->SetParent(pModel->m_pModel[BODY]);															//��̐e��ݒ肷��

	pModel->m_pModel[KATANA] = CModelPart::Create(CModel::MODEL_KATANA, D3DXVECTOR3(-0.0f, -30.5f, 0.0f), D3DXVECTOR3(2.92f, -1.29f, 0.47f ));	//���̃��f���𐶐�����
	pModel->m_pModel[KATANA]->SetParent(pModel->m_pModel[RIGHT_HAND]);														//���̐e��ݒ肷��

	//�����������f�����A�j���[�^�[�ɑ������
	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[HEAD]);
	vParts.push_back(pModel->m_pModel[LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[RIGHT_FOOT]);
	vParts.push_back(pModel->m_pModel[SAYA]);
	vParts.push_back(pModel->m_pModel[KATANA]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);	

	vParts.clear();
	vParts.shrink_to_fit();

	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(30.0f, 175.0f, 30.0f), CHitbox::TYPE_PLAYER, pModel);

	if (pModel->m_pHitbox)
	{
		pModel->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_OBSTACLE, CHitbox::RESPONSE_OVERLAP);
		pModel->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_BUTTON, CHitbox::RESPONSE_OVERLAP);
		pModel->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_VANISHING, CHitbox::RESPONSE_OVERLAP);
		pModel->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_FALL, CHitbox::RESPONSE_OVERLAP);
		pModel->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_OVERLAPPABLE, CHitbox::RESPONSE_OVERLAP);
	}

	return pModel;					//���������C���X�^���X��Ԃ�
}

//�v���C���[�̐F�̎擾����
D3DXCOLOR* CPlayer::GetPlayerColors(void)
{
	return m_playerColor;
}

//�v���C���[�̃L�[����
void CPlayer::PlayerController(int nCntPlayer)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (!m_bAttacking)
	{
		//�ړ��ʂƖړI�̊p�x�̌v�Z
		if (CInputKeyboard::GetKeyboardPress(DIK_W))
		{//W�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.75f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.25f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
			else
			{//W�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.5f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_S))
		{//S�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.75f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.25f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
			else
			{//S�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.5f + fA;

				if (!m_bMoving && !m_bJump)
				{
					m_bMoving = true;

					if (m_pAnimator)
					{
						m_pAnimator->SetPresentAnim(STATE_RUNNING);
					}
				}
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//D�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}

			m_DestRot.y = fA;

			if (!m_bMoving && !m_bJump)
			{
				m_bMoving = true;

				if (m_pAnimator)
				{
					m_pAnimator->SetPresentAnim(STATE_RUNNING);
				}
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//A�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			m_DestRot.y = D3DX_PI + fA;

			if (!m_bMoving && !m_bJump)
			{
				m_bMoving = true;
				
				if (m_pAnimator)
				{
					m_pAnimator->SetPresentAnim(STATE_RUNNING);
				}
			}
		}
	}

	//SPACE�L�[�������ꂽ�ꍇ
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && !m_bJump && !m_bAttacking && m_move.y < 0.0f)
	{//�W�����v
		m_move.y = 30.0f;
 		m_bJump = true;
		m_bLanded = false;

		if (m_pAnimator != nullptr)
		{
			m_pAnimator->SetPresentAnim(CPlayer::STATE_JUMP_START);
		}
	}

	//�U���L�[��������Ă��鎞
	if (CInputKeyboard::GetKeyboardTrigger(DIK_V) &&  !m_bJump && m_bLanded && !m_bHit && !m_bAttacking)
	{
		m_bAttacking = true;
		m_nCntAttack = 19;
	}

}


void CPlayer::SetFriction(const float fFriction)
{
	m_fFrictionCoeff = fFriction;
}

void CPlayer::TransformUpdate(void)
{
	m_LastPos = m_pos;				//�O��̈ʒu�̍X�V

	if (!CApplication::GetFade() && !m_bFall)
	{//�t�F�[�h���Ă��Ȃ�������
		PlayerController(0);		//�v���C���[�𓮂���
	}

	//�ʒu�̍X�V
	m_pos += m_move;

	m_move.x += (0.0f - m_move.x) * m_fFrictionCoeff;		//�ړ��ʂ�X�R���|�l���g�̍X�V
	m_move.y += (0.0f - m_move.y) * 0.1f;					//�ړ��ʂ�Y�R���|�l���g�̍X�V
	m_move.z += (0.0f - m_move.z) * m_fFrictionCoeff;		//�ړ��ʂ�Z�R���|�l���g�̍X�V

	UpdateRotation();

	//�d�ʂ�ǉ�����
	if (m_move.y >= -15.0f)
	{
		m_move.y -= 0.8f;
	}
}

void CPlayer::UpdateRotation(void)
{
	//�ړI�̊p�x�̐��K������
	if (m_DestRot.y - (m_rot.y) > D3DX_PI)
	{
		m_DestRot.y -= 2 * D3DX_PI;
	}
	else if (m_DestRot.y - (m_rot.y) < -D3DX_PI)
	{
		m_DestRot.y += 2 * D3DX_PI;
	}


	//��]�p�x�̌v�Z
	D3DXVECTOR3 rot = m_rot + ((m_DestRot - m_rot) * 0.1f);

	//��]�p�x�̐ݒ菈��
	//m_pModel[BODY]->SetRot(rot);		

	//��]�p�x�̐��K������
	m_rot = rot;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI + (m_rot.y - D3DX_PI);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI - (D3DX_PI + m_rot.y);
	}

	if (m_rot.y < D3DX_PI * -2.0f)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI * 2.0f)
	{
		m_rot.y += D3DX_PI * -2.0f;
	}
}

//�q�b�g�{�b�N�X�̍X�V����
void CPlayer::UpdateHitbox(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(m_pos);
		m_pHitbox->Update();

		if (m_pHitbox->GetCollisionDirection() == CHitbox::FROM_ABOVE)
		{
			m_bLanded = true;
		}
		else if (m_pHitbox->GetCollisionDirection() == CHitbox::FROM_BELOW)
		{
			m_move.y = 0.0f;
		}

		if (D3DXVec3Length(&m_pHitbox->GetMove()) != 0.0f)
		{
			m_pos += m_pHitbox->GetMove();
			m_pHitbox->SetMove(Vec3Null);
		}

		if (D3DXVec3Length(&m_pHitbox->GetAcceleration()) != 0.0f)
		{
			m_move += m_pHitbox->GetAcceleration();
			m_pHitbox->SetAcceleration(Vec3Null);
		}

		HitboxEffectUpdate();
	}
}

void CPlayer::UpdateAnimation(void)
{
	if (m_pAnimator != nullptr)
	{
		//�A�j���[�V�����̍X�V
		m_pAnimator->Update();

		if (!m_bJump && m_bMoving)
		{
			D3DXVECTOR3 residualMove = m_move;
			residualMove.y = 0.0f;

			if (D3DXVec3Length(&residualMove) <= 0.1f)
			{
				m_pAnimator->SetPresentAnim(STATE_NEUTRAL);
				m_bMoving = false;
			}
		}

		if (m_bJump && m_bLanded)
		{
			m_bJump = false;

			if (!m_bMoving)
			{
				m_pAnimator->SetPresentAnim(CPlayer::STATE_NEUTRAL);
			}
			else
			{
				m_pAnimator->SetPresentAnim(CPlayer::STATE_RUNNING);
			}
		}
	}
}

void CPlayer::FieldUpdate(void)
{
	if (m_move.y <= 0.0f)
	{
		float fHeight = 0.0f;

		if (!m_bFall)
		{
			//���b�V���t�B�[���h�Ƃ̓����蔻��
			CMeshfield* pField = CMeshfield::FieldInteraction(this, &fHeight);

			//�n�ʂƂ̓����蔻��
			if (pField != nullptr)
			{
				if (m_bJump)
				{
					if (m_pAnimator)
					{

						m_bJump = false;		//���n���Ă����Ԃɂ���
						m_bLanded = true;

						if (!m_bMoving)
						{
							m_pAnimator->SetPresentAnim(CPlayer::STATE_NEUTRAL);
						}
						else
						{
							m_pAnimator->SetPresentAnim(CPlayer::STATE_RUNNING);
						}
					}
				}

				m_bHit = false;			//�������ĂȂ���Ԃɂ���
										//���C�W���̎擾
				m_fFrictionCoeff = pField->GetFriction();

				//�e�̍����̐ݒ�
				for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
				{
					if (m_pModel[nCnt] != nullptr)
					{
						m_pModel[nCnt]->SetShadowHeight(fHeight);
					}
				}
			}
		}
	}
}

void CPlayer::RespawnPlayer(void)
{
	m_pos = m_respawnPoint;

	m_nInvincibilityCnt = 90;
	m_pHitbox->SetInvincibility(true);
}

void CPlayer::HitboxEffectUpdate(void)
{
	CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

	switch (effect)
	{
	case CHitbox::EFFECT_DAMAGE:

	{
		D3DXVECTOR3 dir = m_pHitbox->GetDirection();

		m_move.x = 0.0f;
		m_move.y = 15.0f;
		m_move.z = 0.0f;

		if (m_pHitbox->GetScore() < 0)
		{
			m_nInvincibilityCnt = 90;
			m_pHitbox->SetInvincibility(true);
		}

		m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
	}

	break;

	case CHitbox::EFFECT_LAUNCH:

		break;

	case CHitbox::EFFECT_PUSH:
		break;

	case CHitbox::EFFECT_BOUNCE:

	{
		D3DXVECTOR3 dir = m_pHitbox->GetDirection();

		m_move.x = dir.x * 20.0f;
		m_move.y = 15.0f;
		m_move.z = dir.z * 20.0f;

		if (m_pHitbox->GetScore() < 0)
		{
			m_nInvincibilityCnt = 90;
			m_pHitbox->SetInvincibility(true);
		}

		m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
	}

	break;

	case CHitbox::EFFECT_JUMP:
		break;

	case CHitbox::EFFECT_FALL:

	{
		m_bFall = true;

		m_move.x = 0.0f;
		m_move.z = 0.0f;

		m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
	}

		break;

	default:
		break;
	}
}

void CPlayer::UpdatePlayerCamera(void)
{
	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetPos(m_pos + m_cameraPos, m_pos + m_baseFocalPointPos);

		if (m_bMoveCamera)
		{
			MoveCamera();
		}
	}
}

void CPlayer::MoveCamera(void)
{

	D3DXVECTOR3 distance = m_cameraTarget - m_cameraPos;			//�ړI�̈ʒu�܂ł̋������v�Z����

	if (D3DXVec3Length(&distance) > 1.0f)
	{
		D3DXVec3Normalize(&distance, &distance);

		m_cameraPos += distance;
	}
	else
	{
		m_bMoveCamera = false;
	}

	m_cameraTarget = m_baseCameraPos;
}
