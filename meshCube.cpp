//=============================================================================
//
// meshcube.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "meshCube.h"
#include "object2D.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"
#include "BoxHitbox.h"

std::vector <CMeshCube*> CMeshCube::m_vMeshCube;		//���b�V���ւ̃|�C���^�̃x�N�g��

//�R���X�g���N�^
CMeshCube::CMeshCube()
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_OriginalPos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_nPriority = 3;
	m_fShadowHeight = 0.0f;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;

	m_vMeshCube.push_back(this);
}

//�R���X�g���N�^
CMeshCube::CMeshCube(const int nPriority) : m_nPriority(nPriority)
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_OriginalPos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_fShadowHeight = 0.0f;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;

	m_vMeshCube.push_back(this);
}

//�f�X�g���N�^
CMeshCube::~CMeshCube()
{

}

//����������
HRESULT CMeshCube::Init(void)
{
	//�����o�[�ϐ�������������
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_OriginalPos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_fShadowHeight = -199.0f;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CMeshCube::Uninit(void)
{
	//���_�o�b�t�@�̔j������
	if (m_pVtxBuff != nullptr)
	{//null�`�F�b�N
		m_pVtxBuff->Release();			//���������������
		m_pVtxBuff = nullptr;			//�|�C���^��null�ɂ���
	}
	//�C���f�b�N�X�o�b�t�@�̔j������
	if (m_pIdxBuff != nullptr)
	{//null�`�F�b�N
		m_pIdxBuff->Release();			//���������������
		m_pIdxBuff = nullptr;			//�|�C���^��null�ɂ���
	}
	//�e�N�X�`���ւ̃|�C���^��null�ɂ���
	if (m_pTexture != nullptr)
	{//null�`�F�b�N
		m_pTexture = nullptr;			//�|�C���^��null�ɂ���
	}
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	int a = m_vMeshCube.size();

	//���̃C���X�^���X�̃A�h���X������
	for (int nCnt = 0; nCnt < a; nCnt++)
	{
		if (m_vMeshCube.data()[nCnt] == this)
		{
			m_vMeshCube.erase(m_vMeshCube.begin() + nCnt);
			break;
		}
	}
}

//�X�V����
void CMeshCube::Update(void)
{
	/*m_rot.y += D3DX_PI * 0.005f;
	m_rot.x += D3DX_PI * 0.001f;*/

	if (D3DXVec3Length(&m_move) > 0.0f)
	{//���x��0�ł͂Ȃ�������

		m_pos += m_move;				//�ʒu�̍X�V

		//�q�b�g�{�b�N�X�̍X�V
		if (m_pHitbox)
		{//null�`�F�b�N
			m_pHitbox->SetPos(m_pos);	//�q�b�g�{�b�N�X�̈ʒu�̍X�V
		}

		ClampMove();				//�ړ��𐧌����鏈��
	}
}

//�`�揈��
void CMeshCube::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans, mtxShadow;											//�v�Z�p�}�g���b�N�X
	D3DXVECTOR4 vecLight;							//���C�g�̌���
	D3DXVECTOR3 pos, Normal;						//���e�p�̈ʒu�Ɩ@��
	D3DXPLANE planeField;							//��

													//���C�g�̌�����ݒ肷��
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, m_fShadowHeight, 0.0f);				//�ʂ̍���
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//�ʂ̖@��

																//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//�����h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̕`��p�̃}�g���b�N�X�����
	D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	VERTEX_3D* pVtx = nullptr;
	D3DXCOLOR col[8] = {};

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		col[nCnt] = pVtx[nCnt].col;
		pVtx[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�̕`�揈��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		pVtx[nCnt].col = col[nCnt];
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`�揈��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`�揈��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);

	pDevice->SetTexture(0, NULL);
}

//�ʒu�̐ݒ菈��
void CMeshCube::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//���x�̐ݒ菈��
void CMeshCube::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�v���C�I���e�B�̐ݒ菈��
void CMeshCube::SetPriority(const int nPriority)
{
	m_nPriority = nPriority;
}

//�T�C�Y�̎擾����
const D3DXVECTOR3 CMeshCube::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CMeshCube::GetPos(void)
{
	return m_pos;
}

//���C�W���̎擾����
const float CMeshCube::GetFriction(void)
{
	return m_fFriction;
}

//�e�N�X�`���̐ݒ菈��
void CMeshCube::SetTexture(CObject::TextType texture)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(texture);		//���[�h�����e�N�X�`���̃|�C���^���擾
	m_pTexture = text;														//�e�N�X�`����ݒ肷��
}




//=============================================================================
//
//								�ÓI�֐�	
//
//=============================================================================




//��������
CMeshCube* CMeshCube::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CMeshCube* pCube = new CMeshCube;			//�C���X�^���X�̐���

	if (FAILED(pCube->Init()))
	{//����������
		return nullptr;
	}

	pCube->m_pos = pos;				//�ʒu�̐ݒ�
	pCube->m_rot = rot;				//�����̐ݒ�
	pCube->m_size = size;			//�T�C�Y�̐ݒ�

	pCube->SetVertex();				//���_�̐ݒ菈��

	pCube->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -size.y, 0.0f),
		D3DXVECTOR3(size.x, size.y * 2.0f, size.z), CHitbox::TYPE_NEUTRAL, pCube);				//�q�b�g�{�b�N�X�̐���

	return pCube;					//���������C���X�^���X��Ԃ�
}

//��������
CMeshCube* CMeshCube::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const D3DXVECTOR3 move, const float fRange)
{
	CMeshCube* pCube = new CMeshCube;			//�C���X�^���X�̐���

	if (FAILED(pCube->Init()))
	{//����������
		return nullptr;
	}

	pCube->m_pos = pos;				//�ʒu�̐ݒ�
	pCube->m_rot = rot;				//�����̐ݒ�
	pCube->m_size = size;			//�T�C�Y�̐ݒ�
	pCube->m_move = move;			//���x�̐ݒ�
	pCube->m_OriginalPos = pos;		//���̈ʒu�̐ݒ�
	pCube->m_fRange = fRange;		//�ړ��̌��E�̐ݒ�

	pCube->SetVertex();				//���_�̐ݒ菈��

	pCube->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -size.y, 0.0f),
		D3DXVECTOR3(size.x, size.y * 2.0f, size.z), CHitbox::TYPE_NEUTRAL, pCube);				//�q�b�g�{�b�N�X�̐���

	if (pCube->m_pHitbox)
	{//�q�b�g�{�b�N�X�������o������

		pCube->m_pHitbox->SetMove(move);				//�q�b�g�{�b�N�X�̑��x�̐ݒ�
	}

	return pCube;					//���������C���X�^���X��Ԃ�
}

//�����蔻��̏���
bool CMeshCube::CubeInteraction(CObject* pObj)
{
	return false;
}

//�����蔻��̏���
CMeshCube* CMeshCube::CubeInteraction(CObject* pObj, float* fHeight)
{
	return nullptr;
}

void CMeshCube::ClearCubes(void)
{

}



//=============================================================================
//
//							�v���C�x�[�g�֐�	
//
//=============================================================================



//���_�C���f�b�N�X�̐ݒ菈��
void CMeshCube::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_nVertexNumber = 8;
	m_nIndexNumber = 22;
	m_nPolygonNumber = 20;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);

	pVtx[4].pos = D3DXVECTOR3(-m_size.x, -m_size.y, m_size.z);
	pVtx[5].pos = D3DXVECTOR3(m_size.x, -m_size.y, m_size.z);
	pVtx[6].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[7].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);

	//D3DXCOLOR C[6] = { ColorRed, ColorGreen, ColorBlue, ColorYellow, ColorCyan, ColorMagenta };

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		D3DXVECTOR3 N = pVtx[nCnt].pos;
		D3DXVec3Normalize(&N, &N);
		pVtx[nCnt].nor = N;
		pVtx[nCnt].col = /*C[random(0, 5)]*/ColorWhite;
		pVtx[nCnt].tex = Vec2Null;

	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	WORD*pIdx;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 2;
	pIdx[1] = 0;
	pIdx[2] = 3;
	pIdx[3] = 1;

	pIdx[4] = 1;
	pIdx[5] = 5;
	pIdx[6] = 5;
	pIdx[7] = 1;
	pIdx[8] = 4;
	pIdx[9] = 0;
	pIdx[10] = 6;
	pIdx[11] = 2;
	pIdx[12] = 7;
	pIdx[13] = 3;
	pIdx[14] = 5;
	pIdx[15] = 1;

	pIdx[16] = 1;
	pIdx[17] = 4;

	pIdx[18] = 4;
	pIdx[19] = 6;
	pIdx[20] = 5;
	pIdx[21] = 7;

	m_pIdxBuff->Unlock();
}

//�ړ��𐧌�����
void CMeshCube::ClampMove(void)
{
	if (m_pos.x <= m_OriginalPos.x - m_fRange)
	{
		m_pos.x = m_OriginalPos.x - m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (m_pos.y <= m_OriginalPos.y - m_fRange)
	{
		m_pos.y = m_OriginalPos.y - m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (m_pos.z <= m_OriginalPos.z - m_fRange)
	{
		m_pos.z = m_OriginalPos.z - m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}

	if (m_pos.x >= m_OriginalPos.x + m_fRange)
	{
		m_pos.x = m_OriginalPos.x + m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (m_pos.y >= m_OriginalPos.y + m_fRange)
	{
		m_pos.y = m_OriginalPos.y + m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (m_pos.z >= m_OriginalPos.z + m_fRange)
	{
		m_pos.z = m_OriginalPos.z + m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
}
