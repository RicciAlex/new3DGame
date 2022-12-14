

float4x4 m_WVP;                   //�ϊ��}�g���b�N�X
float4 m_LightDir;                //���s�����̕����x�N�g��
float4 m_EyePos;                  //���_�x�N�g��(posV)
float  m_Specular = 0.0f;         //�X�y�L�����[�͈̔�
float  m_SpecularPower = 0.0f;    //�X�y�L�����[�̋��x
float  m_Alpha;                   //�����x

sampler tex0 : register(s0);      //�e�N�X�`���[

struct VS_OUTPUT
{
	float4 Pos      : POSITION;				//���_�̈ʒu
	float2 Tex      : TEXCOORD0;			//���_�̃e�N�X�`�����W
	float3 Normal   : TEXCOORD1;			//���_�̖@��
	float3 Eye      : TEXCOORD2;			//���_���王�_�܂ł̃x�N�g��
};

VS_OUTPUT VS(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVP);			//���_���W��ϊ�����
	Out.Tex = Tex;						//�e�N�X�`�����W�����̂܂܊i�[����

	//�I�u�W�F�N�g�̖@���x�N�g���𐳋K������
	Out.Normal = Normal.xyz;

	//���_���王�_�܂ł̃x�N�g�����v�Z����
	Out.Eye = m_EyePos.xyz - Pos.xyz;

	return Out;
}

float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

//�C���v�b�g�̃x�N�g���𐳋K������
float3 N = normalize(In.Normal);
float3 E = normalize(In.Eye);

//�n�[�t�����o�[�g���C�e�B���O�Ōv�Z����
float d = dot(N, E);				//�@���ƒ��_���王�_�܂ł̃x�N�g���̊Ԃ̊p�x�̃R�T�C�����v�Z����
float p = d * 0.5f + 0.5;			//0�`1�̊Ԃɕϊ�����
p = p * p;							

//�F�����e�N�Z���̂t�����Ƃ��āA�����e�N�X�`���[������̔��˗����擾����
Out = tex2D(tex0, float2(p, In.Tex.y));

//�n�C���C�g�̌v�Z
float3 H = normalize(-m_LightDir.xyz + E.xyz);
float S = pow(max(0.0f, dot(N, H)), m_Specular) * m_SpecularPower;

Out.rgb = Out.rgb + S;

//�����x�͖@���x�N�g���Ǝ����x�N�g���Ƃ̓��ς��������قǍ����Ȃ�悤�ɂ���
d = d * m_Alpha;
Out.a = 1.0f - d + S;

return Out;
}

technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
}