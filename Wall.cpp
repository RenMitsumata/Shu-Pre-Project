#define NOMINMAX
#include "Wall.h"
#include "CollisionOBB.h"
#include "Model.h"


Wall::Wall()
{
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	pos = XMFLOAT3(0.0f, 1.0f, 5.0f);
	rot = XMFLOAT3(0.0f, 1.5f + XM_PIDIV2, 0.0f);
	XMVECTOR rotVec = XMQuaternionRotationAxis(XMLoadFloat3(&up), 1.5f);
	XMVECTOR frontVec = XMLoadFloat3(&front);
	XMVector3Rotate(frontVec, rotVec);
	frontVec = XMVector3Normalize(frontVec);
	XMStoreFloat3(&front, frontVec);
	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/wall.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);
	CollisionOBB* col = ComponentFactory::CreateComponent<CollisionOBB>();
	col->SetOwner(this);
	componentsList.push_back(col);
}


Wall::~Wall()
{
}
