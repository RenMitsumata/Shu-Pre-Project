
/*
 *   structures
 */
struct PS_IN
{
	float4 pos		: SV_POSITION;
	float3 worldPos : POSITION1;
	float3 tangent	: TANGENT0;
	float3 binormal	: BINORMAL0;
	float3 normal	: NORMAL0;
	float2 texcoord : TEXCOORD0;
};

struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit���E�p
};


/*
 *   constant buffers
 */
cbuffer ConstantBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	matrix WorldViewProjection;
	matrix WorldInvTransMatrix;
	float4 cameraPos;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL	Material;
}


Texture2D outTexture : register(t0);	// VRAM��t0�ɓo�^����Ă���f�[�^�́uoutTexture�v�Ƃ��Ĉ�����
Texture2D normalTexture : register(t1);

SamplerState samplerState : register(s0);



float4 main(in PS_IN input) : SV_TARGET{
	
	
	float3 normalMap = (normalTexture.Sample(samplerState,input.texcoord)) * 2.0f - 1.0f;
	normalMap = normalize(normalMap);

	// �}�C�i�X�̋L���͐l�ɂ���ĈႤ����A�ڂŌ��Ă��
	float3 normalW = normalize(normalMap.x * input.tangent + normalMap.y * input.binormal + normalMap.z * input.normal);

	
	// �p�[�s�N�Z�����C�e�B���O
	// ���C�g�x�N�g��(��)->���W�X�^�ɏ�������āACPU�����瑗��
	// ���C�g�J���[������āA���W�X�^���瑗��
	float3 lightDir = float3(1.0f, -1.0f, 1.0f);
	lightDir = normalize(lightDir);
	// �n�[�t�����o�[�g
	float light = (dot(normalize(-lightDir), normalW));
	light = saturate(light);	// light = max(light,0.0f);

	// �m�F�p

	float4 posW = mul(input.pos, World);

	
	
	// ���˃x�N�g�������߂�
	float3 refVec = reflect(lightDir,normalW);
	float3 eyev = input.worldPos - cameraPos.xyz;	// posW�͌��点�������W�����̃x�N�g��
	refVec = normalize(refVec);
	eyev = normalize(eyev);

	float specular = dot(normalize(-refVec),normalize(eyev));
	specular = saturate(specular);
	specular = pow(specular, 50);	// pow(�,�w��) -> �w���̕����̓��W�X�^�ɏ������ނׂ����X�y�L�����p���[
	float4 specularColor = float4(specular, specular, specular, 1.0f);
	// specular�́APS���Ńe�N�X�`���̐F�ɉ��Z���ďo����VS�̏o�́APS�̓��͂Ƀ��C�A�E�g��ǉ�����
	
	
	// �����}�b�s���O
	
	float3 toEyeT;	// �����̃e�N�X�`�����W�n�̍��W
	toEyeT.x = dot(cameraPos, -input.binormal);
	toEyeT.y = dot(cameraPos, input.tangent);
	toEyeT.z = dot(cameraPos, input.normal);



	float height = (normalTexture.Sample(samplerState, input.texcoord)).a * 2.0f - 1.0f;	// a�͍����}�b�s���O�̃O���[�X�P�[���l

	float2 parallax_uv = input.texcoord + height * 0.2f * toEyeT.xy;	// 0.2f�͍����}�b�s���O�̐��x�ɂ��ς��� �{��聨�͂��炵������
	
	

	//�@�@�@�@������Ŗ@���ƐF���e�N�X�`������Ƃ��Ă���

	/*

	float3 rayDir = input.pos.xyz - cameraPos.xyz;
	rayDir = normalize(rayDir);
	const float HEIGHT_MAX = 0.02f;

	float4 Out;

	float3 Eye;
	Eye.x = dot(rayDir, -input.tangent);
	Eye.y = dot(rayDir, input.binormal);
	Eye.z = dot(rayDir, input.normal);
	rayDir = Eye;


	//���_���W�`��ł̊e�x�N�g��
	float3 E = normalize(Eye);
	float3 L = normalize(lightDir);

	//�X�N���[����Ԃ� x,y ���W�ɂ��āAx.y �̌��z���擾
	float2 dx, dy;
	dx = ddx(input.texcoord);
	dy = ddy(input.texcoord);

	//���_���W�n��ł̖@���x�N�g��
	float3 N = input.normal;

	//�e�N�Z���̃T���v�����O�ʒu�̃I�t�Z�b�g�l�𒲐�����
	float2 offset = E.xy * 0.02f;

	//�e�N�Z���̃T���v�����O�ʒu
	float2 texel = input.texcoord;

	float height = 0.0f;

	bool flg = false;

	for(int i=0;i<33;i++)
	{
		
		float4 NormalMap = normalTexture.Sample(samplerState, texel);

		//�����Ŕ�r����
		if (NormalMap.a * HEIGHT_MAX <= height)
		{
			//�@���x�N�g�����擾
			float3 Normal = 2.0f * NormalMap.rgb - 1.0f;

			//�n�[�t�����o�[�g�g�U�Ɩ�
			float color = dot(Normal,lightDir);
			color = color * 0.5f + 0.5f;
			color = color * color;

			Out = outTexture.Sample(samplerState, texel) * color;
			

			//���[�v�I��
			flg = true;
			break;
		}

		texel += offset;
		height += E.z * 0.02f;
	}

	Out = float4(Out.xyz, 1.0f);
	return Out + specular;


	*/




	/*

	
	const int DIVISION_NUM = 32;
	const float HEIGHT_MAX = 0.2f;
	float3 rayDir = input.worldPos - cameraPos.xyz;
	rayDir = normalize(rayDir);
	float length = 1.0f * HEIGHT_MAX / DIVISION_NUM;
	float3 deltaRay = rayDir * length;
	float3 rayPos = input.worldPos;
	float objHeight = -HEIGHT_MAX;
	float rayHeight = 0.0f;


	
	for (int i = 0; i < DIVISION_NUM&&objHeight < rayHeight; i++) {
		rayPos += deltaRay;	// ���������ɐi�߂�
		objHeight = normalTexture.Sample(samplerState, rayPos.xz).a;
		objHeight = objHeight * HEIGHT_MAX - HEIGHT_MAX;
		rayHeight = rayPos.y;
	}
	
	float2 parallax_uv = rayPos.xz;
	

	*/

	//return outTexture.Sample(samplerState, input.texcoord);

	return float4(outTexture.Sample(samplerState, parallax_uv).rgb * light,1.0f) + specularColor;

	


	
}