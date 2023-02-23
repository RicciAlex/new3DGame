//=============================================================================
//
// stageSelectCursor.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stageSelectCursor.h"
#include "model.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CStageSelectCursor::RELATIVE_POS[JEWEL_NUMBER] = {
	{ 250.0f, 0.0f, 0.0f },
	{ 216.5f, 0.0f, 125.0 },
	{ 125.0, 0.0f, 216.5f },
	{ 0.0f, 0.0f, 250.0f },
	{ -125.0, 0.0f, 216.5f },
	{ -216.5f, 0.0f, 125.0 },
	{ -250.0f, 0.0f, 0.0f },
	{ -216.5f, 0.0f, -125.0 },
	{ -125.0, 0.0f, -216.5f },
	{ 0.0f, 0.0f, -250.0f },
	{ 125.0, 0.0f, -216.5f },
	{ 216.5f, 0.0f, -125.0 }

};		//��΂̑��Έʒu


const D3DXCOLOR CStageSelectCursor::JEWEL_COLOR[JEWEL_NUMBER / 2] = {
	ColorRed,
	ColorGreen,
	ColorBlue,
	ColorYellow,
	ColorCyan,
	ColorMagenta

};		//��΂̐F

//�R���X�g���N�^
CStageSelectCursor::CStageSelectCursor()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;

	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CStageSelectCursor::~CStageSelectCursor()
{

}

//����������
HRESULT CStageSelectCursor::Init(void)
{
	return S_OK;
}

//�I������
void CStageSelectCursor::Uninit(void)
{
	//���f���̔j������
	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		if (m_pModel[nCnt])
		{//null�`�F�b�N
			m_pModel[nCnt]->Release();		//���������������
			m_pModel[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}
}

//�X�V����
void CStageSelectCursor::Update(void)
{

}

//�`�揈��
void CStageSelectCursor::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CStageSelectCursor::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		m_pModel[nCnt]->SetPos(m_pos + RELATIVE_POS[nCnt]);
	}
}

//�ʒu�̎擾����
const D3DXVECTOR3 CStageSelectCursor::GetPos(void)
{
	return m_pos;
}





//��������
CStageSelectCursor * CStageSelectCursor::Create(const D3DXVECTOR3 pos)
{
	CStageSelectCursor* pCursor = new CStageSelectCursor;			//�C���X�^���X�𐶐�����

	if(FAILED(pCursor->Init()))
	{//����������
		return nullptr;
	}

	pCursor->m_pos = pos;			//�ʒu�̐ݒ�

	//��΂̐�������
	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		pCursor->m_pModel[nCnt] = CModel::Create(CModel::MODEL_JEWEL, pos + RELATIVE_POS[nCnt]);

		if (pCursor->m_pModel[nCnt])
		{//�����o������A�F��ݒ肷��
			pCursor->m_pModel[nCnt]->SetModelColor(1, JEWEL_COLOR[nCnt % (JEWEL_NUMBER / 2)]);
			pCursor->m_pModel[nCnt]->SetScale(1.5f);
			pCursor->m_pModel[nCnt]->SetShadowDraw(false);
			pCursor->m_pModel[nCnt]->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.005f, 0.0f));
		}
	}

	return pCursor;				//���������C���X�^���X��Ԃ�
}
