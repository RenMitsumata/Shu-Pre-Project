#pragma once

#include "main.h"
#include "Component.h"
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
//#include <assimp\matrix4x4.h>
//#include <assimp/texture.h>
//#pragma comment (lib,"assimp.lib")

#include "DXManager.h"
#include "Manager.h"
#include "Shader3D.h"
#include "Texture.h"
#include "GameObject.h"
#include <unordered_map>
#include <vector>

// �m�[�h�\���́B�q�m�[�h�Ȃǂ̏����m��
struct NODE {	// <-- delete[]��Y�ꂸ�ɁI
	NODE* parentNode;
	NODE** childNode;
	unsigned int childNum;
	unsigned int* meshIndex;
	unsigned int meshNum;
	const char* nodeName;
	XMFLOAT4X4 offsetMatrix;
};

// ���b�V���\����
struct MESH {
	unsigned int indexOffset;
	unsigned int indexNum;
	unsigned int materialIndex;
};

// �A�j���[�V�����p���_�\����
struct DEFORM_VERTEX {
	XMFLOAT3 position;
	XMFLOAT3 deformPosition;
	XMFLOAT3 normal;
	XMFLOAT3 deformNormal;
	int boneNum;
	// int boneIndex[4];	�������ق�
	std::string boneName[4];
	float boneWeight[4];

};

// �A�j���[�V�����p�{�[���̍\����
struct BONE {
	// std::string name;
	XMFLOAT4X4 matrix;
	XMFLOAT4X4 animationMatrix;
	XMFLOAT4X4 offsetMatrix;
};

// �A�j���[�V�����̃f�[�^���i�[����\����
struct ANIM_CHANNEL {
	std::unordered_map<std::string, XMFLOAT4>* rotDatas;	// �N�H�[�^�j�I��
	std::unordered_map<std::string, XMFLOAT3>* posDatas;
};

struct ANIM_DATA {
	ANIM_CHANNEL* channels;
};



class Model : public Component
{
private:
	Manager* manager;
	Shader3D* shader;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Texture** textureList;
	unsigned int textureNum;
	MATERIAL** materialList;
	unsigned int materialNum;
	VERTEX_3D* vertexList;
	MESH* meshList;
	unsigned short* indexList;
	NODE* rootNode;

	// �A�j���[�V�����֘A
	std::vector<DEFORM_VERTEX>* pDeformVertexs;
	std::unordered_map<std::string, BONE> Bones;
	ANIM_DATA* animData;
	unsigned int animNum;
	unsigned int* animChannels;	// FBX�t�@�C���P�ɂ��A�����A�j���[�V�����ɂ���Ƃ��͔z��ɂ���

	void CreateBone(NODE* node);
	void UpdateBoneMatrix(NODE* node, XMFLOAT4X4* defMat);

	NODE* RegisterNode(aiNode* pNode);
	void DeleteNode(NODE* node);
	void DrawNode(NODE* node, XMMATRIX mat);
public:
	Model();
	~Model();
	void Update()override;
	void Draw()override;
	void Load(const char* filename);
	void Uninit()override;
};

