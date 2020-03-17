
/*
 *   structures
 */
struct PS_IN
{
	float4 pos		: SV_POSITION;
	float3 cameraPos : POSITION1;
	float2 texcoord : TEXCOORD0;
};




Texture2D outTexture : register(t0);	// VRAM��t0�ɓo�^����Ă���f�[�^�́uoutTexture�v�Ƃ��Ĉ�����
Texture2D posTexture : register(t1);
Texture2D normalTexture : register(t2);
Texture2D depthTexture: register(t3);

SamplerState samplerState : register(s0);



float4 main(in PS_IN input) : SV_TARGET{

	float4 outDiffuse;
	//�u���[������
	float4 diffuse;
	for(int y = -10; y < 11; y++){
		for(int x = -10; x < 11; x++){
			float2 texcoord = input.texcoord + float2(x*2/960.0f,y*2/540.0f);	// �K�E�X�t�B���^�[(1�s�N�Z���ƂȂ��UV�łǂꂭ�炢�H)
			float4 color = outTexture.Sample(samplerState,texcoord);
			float light = color.r * 0.299f + color.g * 0.587f + color.b * 0.114f;	// �P�x
			if(light > 1.0f && (x != 0 || y != 0)){
				diffuse += color / (x * x + y * y);
			}
		}
	}
	outDiffuse = outTexture.Sample(samplerState,input.texcoord);
	outDiffuse += diffuse * 0.5f;
	outDiffuse.a = 1.0f;



	// �p�[�s�N�Z�����C�e�B���O
	// ���C�g�x�N�g��(��)->���W�X�^�ɏ�������āACPU�����瑗��
	// ���C�g�J���[������āA���W�X�^���瑗��
	float3 lightDir = float3(1.0f, -1.0f, 1.0f);
	lightDir = normalize(lightDir);

	// �n�[�t�����o�[�g	
	float light = (dot(normalize(-lightDir), normalTexture.Sample(samplerState, input.texcoord).xyz));
	light = saturate(light);	// light = max(light,0.0f);

	// �m�F�p

	float3 posW = posTexture.Sample(samplerState, input.texcoord).xyz;



	// ���˃x�N�g�������߂�
	float3 refVec = reflect(lightDir, normalTexture.Sample(samplerState, input.texcoord).xyz);
	float3 eyev = posW - input.cameraPos.xyz;	// posW�͌��点�������W�����̃x�N�g��
	refVec = normalize(refVec);
	eyev = normalize(eyev);

	float specular = dot(normalize(-refVec),normalize(eyev));
	specular = saturate(specular);
	specular = pow(specular, 50);	// pow(�,�w��) -> �w���̕����̓��W�X�^�ɏ������ނׂ����X�y�L�����p���[
	float4 specularColor = float4(specular, specular, specular, 1.0f);
	// specular�́APS���Ńe�N�X�`���̐F�ɉ��Z���ďo����VS�̏o�́APS�̓��͂Ƀ��C�A�E�g��ǉ�����


	outDiffuse += specularColor;

	return outDiffuse;


	

	////�@�@�@�@������Ŗ@���ƐF���e�N�X�`������Ƃ��Ă���



	////return outTexture.Sample(samplerState, input.texcoord);
	//return float4(outTexture.Sample(samplerState, parallax_uv).rgb * light,1.0f) + float4(specularColor.xyz,0.0f);





}