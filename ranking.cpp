//=============================================================================
//
// ranking.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "ranking.h"
#include "object2D.h"
#include "application.h"
#include "UIString.h"
#include "inputKeyboard.h"
#include "sound.h"

#include <string>

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
CObject::TextType CRanking::TEXT_TYPE[CScore::STAGE_MAX][2] = { { CObject::TEXTURE_GEAR_BG, CObject::TEXTURE_IRON }, { CObject::TEXTURE_SNOW, CObject::TEXTURE_ICE } };		//�w�i�̃e�N�X�`���̎��
const D3DXVECTOR3 CRanking::STRING_POS = { 400.0f, 100.0f, 0.0f };		//�����L���O�̕�����̈ʒu
const D3DXVECTOR3 CRanking::ARROW_POS[2] = { { 100.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f }, { (float)SCREEN_WIDTH - 100.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f } };		//�A���[UI�̈ʒu
const D3DXVECTOR2 CRanking::ARROW_SIZE = { D3DXVECTOR2(75.0f, 75.0f) };		//�A���[UI�̃T�C�Y
const D3DXVECTOR2 CRanking::BG_SIZE[2] = { { (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f }, { (float)SCREEN_WIDTH * 0.35f, (float)SCREEN_HEIGHT * 0.5f } };		//�w�i�̃T�C�Y


//�R���X�g���N�^
CRanking::CRanking()
{
	//�����o�[�ϐ����N���A����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pBg[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < CScore::RANKING_SCORE; nCnt++)
	{
		m_pRank[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CRanking::~CRanking()
{

}

//����������
HRESULT CRanking::Init(void)
{
	CObject_2D* pArrow[2] = {};
	
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pArrow[nCnt] = CObject_2D::Create(4, ARROW_POS[nCnt], ARROW_SIZE, CObject::TEXTURE_GUIDE_ARROW);

		if (pArrow[nCnt])
		{
			pArrow[nCnt]->SetTextureParameter(2, 2, 1, 30);
			pArrow[nCnt]->SetStartingRot(-D3DX_PI * 0.5f);
		}
	}
	
	if (pArrow[1])
	{
		pArrow[1]->FlipY();
	}

	CScore* pScore = CApplication::GetScore();
	int* pRank = nullptr;

	if (pScore)
	{
		m_nPresentStage = pScore->GetStage();

		pRank = pScore->GetRanking(m_nPresentStage);
	}

	CUIString::Create(STRING_POS, D3DXVECTOR2(500.0f, 50.0f), ColorRed, "RANKING");

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pBg[nCnt] = CObject_2D::Create(2, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), BG_SIZE[nCnt], TEXT_TYPE[m_nPresentStage][nCnt]);
	}

	CObject_2D* pObj = CObject_2D::Create(3, D3DXVECTOR3((float)SCREEN_WIDTH - 100.0f, (float)SCREEN_HEIGHT - 100.0f, 0.0f),
		D3DXVECTOR2(50.0f, 100.0f), CObject::TEXTURE_SPACE_KEY);

	if (pObj)
	{
		pObj->SetTextureParameter(2, 2, 2, 30);
		pObj->SetAnimationBase(2);
		pObj->SetAnimPattern(2);
	}

	for (int nCnt = 0; nCnt < CScore::RANKING_SCORE; nCnt++)
	{
		if (pRank)
		{
			std::string strScore = std::to_string(pRank[nCnt]);
			std::string str;
			int nDigit = 6 - strScore.size();
			
			for (int nCnt = 0; nCnt < nDigit; nCnt++)
			{
				str = "0" + strScore;
				strScore = str;
			}

			std::string string = std::to_string(nCnt + 1) + " : " + strScore;
			m_pRank[nCnt] = CUIString::Create(D3DXVECTOR3(350.0f, 250.0f + 100.0f * nCnt, 0.0f), D3DXVECTOR2(500.0f, 50.0f), ColorYellow, string.c_str());
		}
	}

	return S_OK;
}

//�I������
void CRanking::Uninit(void)
{
	//�w�i�̔j������
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pBg[nCnt])
		{//null�`�F�b�N
			m_pBg[nCnt]->Release();		//���������������
			m_pBg[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//UI�̔j������
	for (int nCnt = 0; nCnt < CScore::RANKING_SCORE; nCnt++)
	{
		if (m_pRank[nCnt])
		{//null�`�F�b�N
			m_pRank[nCnt]->Release();		//���������������
			m_pRank[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}
}

//�X�V����
void CRanking::Update(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputKeyboard::GetKeyboardTrigger(DIK_LEFT) ||
		CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT))
	{
		m_nPresentStage ^= 1;

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_pBg[nCnt])
			{
				m_pBg[nCnt]->SetTexture(TEXT_TYPE[m_nPresentStage][nCnt]);
			}
		}

		CScore* pScore = CApplication::GetScore();
		int* pRank = nullptr;

		if (pScore)
		{
			pRank = pScore->GetRanking(m_nPresentStage);
		}

		for (int nCnt = 0; nCnt < CScore::RANKING_SCORE; nCnt++)
		{
			if (pRank)
			{
				std::string strScore = std::to_string(pRank[nCnt]);
				std::string str;
				int nDigit = 6 - strScore.size();

				for (int nCnt = 0; nCnt < nDigit; nCnt++)
				{
					str = "0" + strScore;
					strScore = str;
				}

				std::string string = std::to_string(nCnt + 1) + ":" + strScore;
				m_pRank[nCnt]->ChangeString(string.c_str());
			}
		}

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHOOSH);
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
	{
		CApplication::SetFade(CApplication::MODE_TITLE);
	}
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CRanking* CRanking::Create(void)
{
	CRanking* pRanking = new CRanking;			//�C���X�^���X�𐶐�����

	if (FAILED(pRanking->Init()))
	{//����������
		return nullptr;
	}

	return pRanking;		//���������C���X�^���X��Ԃ�
}