#pragma once

#define NOMINMAX
#include "main.h"
#include "Component.h"
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\matrix4x4.h>
#pragma comment (lib,"assimp.lib")

#include "DXManager.h"
#include "Manager.h"
#include "Shader3D_Normal.h"
#include "Texture.h"
#include "GameObject.h"


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

// ���b�V���\���́B�A�j���[�V�����Ƃ��@���}�b�s���O�Ƃ����ǉ��\��
struct MESH {
	unsigned int indexOffset;
	unsigned int indexNum;
	unsigned int materialIndex;
};


class ModelNormal : public Component
{
private:
	Manager* manager;
	Shader3D_Normal* shader;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Texture** textureList;
	MATERIAL** materialList;
	VERTEX_3D_Normal* vertexList;
	MESH* meshList;
	unsigned short* indexList;
	NODE* rootNode;
	NODE* RegisterNode(aiNode* pNode);
	void DeleteNode(NODE* node);
	void DrawNode(NODE* node, XMMATRIX mat);
	Texture* Normal;
public:
	ModelNormal();
	~ModelNormal();
	void Draw()override;
	void Load(const char* filename);
	void Uninit()override;
};

