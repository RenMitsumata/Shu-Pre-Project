#define NOMINMAX
#include "EnemyState.h"
#include "EnemyStateWander.h"
#include "Enemy.h"
#include "Model.h"
#include "CollisionCone.h"
#include "Billboard.h"
#include "EnemyManager.h"
#include <typeinfo>

Enemy::Enemy()
{
	manager = Manager::Get()->GetEnemyManager();
	if (!manager) {
		assert(false);
	}
	manager->AddEnemy(this);
}


Enemy::~Enemy()
{
	delete[] nodeArray;
	manager->DeleteEnemy(this);
	delete state;
}

void Enemy::Init()
{
	pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	state = new EnemyStateWander;
	state->Init(this);

	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/human2.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);

	CollisionCone* cone = ComponentFactory::CreateComponent<CollisionCone>();
	cone->SetTag(e_COLTYPE_ENEMY_EYESIGHT);
	cone->SetParams(0.3f, 1.0f, 3.0f);
	cone->SetDeltaPos(XMFLOAT3(0.0f, 2.0f, 0.0f));
	cone->SetOwner(this);
	componentsList.push_back(cone);


}

void Enemy::Update()
{
	// �G�l�~�[�X�e�[�g�̃A�b�v�f�[�g�H
	state->Update(this);
}

void Enemy::ColAction(Component* comp)
{
	Billboard* bill = ComponentFactory::CreateComponent<Billboard>();
	bill->SetTexture("Assets/Textures/found.png");
	bill->SetDeltaPos(XMFLOAT3(0.0f, 2.5f, 0.0f));
	bill->SetOwner(this);
	componentsList.push_back(bill);

	// �����Ɍx����Ԃɂ���v���O����
	manager->ChangePhase(e_ENEMYPHASE_ALERT);
}

void Enemy::SetWanderNode(unsigned short* nodeArray, unsigned short num)
{
	std::string type = typeid(*state).name();
	if (type == "class EnemyStateWander") {
		dynamic_cast<EnemyStateWander*>(state)->SetNode(nodeArray, num);
	}
	this->nodeArray = new unsigned short[num];
	memcpy(this->nodeArray, nodeArray, sizeof(unsigned short) * num);
}






//void Enemy::ChangeState(EnemyPhase phase)
//{
//}

