//=============================================================================
//
// guideArrow.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GUIDE_ARROW_H
#define GUIDE_ARROW_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object3D.h"


class CGuideArrow : public CObject_3D
{
public:		
	CGuideArrow();						//コンストラクタ
	~CGuideArrow() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理

	static CGuideArrow* Create(const D3DXVECTOR3 pos);		//生成処理
	static CGuideArrow* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//生成処理

private:

};




#endif