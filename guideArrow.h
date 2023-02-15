//=============================================================================
//
// guideArrow.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GUIDE_ARROW_H
#define GUIDE_ARROW_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"


class CGuideArrow : public CObject_3D
{
public:		
	CGuideArrow();						//�R���X�g���N�^
	~CGuideArrow() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������

	static CGuideArrow* Create(const D3DXVECTOR3 pos);		//��������

private:

};




#endif