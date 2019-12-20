#define NOMINMAX
#include "Bullet.h"
#include "Model.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/ball.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);
}

void Bullet::Update() 
{
	pos += velocity;
}