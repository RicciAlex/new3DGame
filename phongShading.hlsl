

float4x4 m_WVP;					//���[���h�}�g���b�N�X
float4 m_LightDir;				//���C�g�̕���
float4 m_EyePos;                //�J�����̈ʒu�x�N�g��
float4 m_Ambient = 1.0f;		
float4 m_Emissive = 0.0f;
float  m_Specular = 0.0f;       //�X�y�L�����[�͈̔�
float  m_SpecularPower = 0.0f;  //�X�y�L�����[�̋��x

sampler s0 : register(s0);      //�I�u�W�F�N�g�̃e�N�X�`���[

//========================================================
//					Vertex Shader
//========================================================

//���_�V�F�[�_�[�̃A�E�g�v�b�g
struct VS_OUTPUT
{
	float4 Pos    : POSITION;	 //�ʒu
	float4 Col    : COLOR0;		 //�F
	float2 Tex    : TEXCOORD0;	 //�e�N�X�`�����W
	float3 Normal : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
	float3 L      : TEXCOORD2;   //���_ -> ���C�g�ʒu �x�N�g��
	float3 E      : TEXCOORD3;   //���_ -> ���_ �x�N�g��
};

//Vertex Shader
VS_OUTPUT VS(float4 Pos    : POSITION,
			 float4 Normal : NORMAL,
			 float2 Tex    : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVP);			//���_���W�����[�J���ϐ�����O���[�o���ϐ��ւ̕ϊ�
	Out.Tex = Tex;						//�e�N�X�`�����W�����̂܂܊i�[����

	//���C�g�����œ��͂����̂ŁA���_ -> ���C�g�ʒu�Ƃ��邽�߂ɋt�����ɕϊ�����B�Ȃ��A�v���P�[�V�����ŕK�����K�����邱��
	Out.L = -m_LightDir.xyz;

	Out.Normal = Normal.xyz;					//�@���x�N�g�������̂܂܊i�[����

	//���C�g�x�N�g���Ɩ@���x�N�g���̓��ς��v�Z���āA�v�Z���ʂ̐F�̍Œ�l������( m_Ambient )�ɐ�������
	Out.Col = min(max(m_Ambient, dot(Out.Normal, Out.L)) + m_Emissive, 1.0f);

	//���_���王�_ �ւ̃x�N�g�����v�Z
	Out.E = m_EyePos.xyz - Pos.xyz;

	return Out;
}

//========================================================
//					Pixel Shader
//========================================================
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//�@���x�N�g���𐳋K������
	float3 N = normalize(In.Normal);
	
	//���_ -> ���C�g�ʒu�x�N�g�� + ���_ -> ���_�x�N�g��
	float3 H = normalize(In.L + normalize(In.E));
	
	//�X�y�L�����[�J���[���v�Z����
	float S = pow(max(0.0f, dot(N, H)), m_Specular) * m_SpecularPower;
	
	//�X�y�L�����[�J���[�����Z����
	Out = In.Col * tex2D(s0, In.Tex) + S;
	
	return Out;
}

technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}