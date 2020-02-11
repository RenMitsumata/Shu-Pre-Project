#define NOMINMAX
#include "EnemyState.h"
#include "EnemyStateWander.h"
#include "Enemy.h"
#include "Model.h"
#include "CollisionCone.h"
#include "Billboard.h"
#include "EnemyManager.h"

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
	manager->DeleteEnemy(this);
	delete state;
}

void Enemy::Init()
{
	pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	state = new EnemyStateWander;

	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/remy.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);

	CollisionCone* cone = ComponentFactory::CreateComponent<CollisionCone>();
	cone->SetTag(e_COLTYPE_ENEMY_EYESIGHT);
	cone->SetParams(0.3f, 1.0f, 3.0f);
	cone->SetDeltaPos(XMFLOAT3(0.0f, 3.0f, 0.0f));
	cone->SetOwner(this);
	componentsList.push_back(cone);


}

void Enemy::ColAction(Component* comp)
{
	Billboard* bill = ComponentFactory::CreateComponent<Billboard>();
	bill->SetTexture("Assets/Textures/found.png");
	bill->SetDeltaPos(XMFLOAT3(0.0f, 4.0f, 0.0f));
	bill->SetOwner(this);
	componentsList.push_back(bill);

	// ‚±‚±‚ÉŒx‰úó‘Ô‚É‚·‚éƒvƒƒOƒ‰ƒ€
	manager->ChangePhase(e_ENEMYPHASE_ALERT);
}

void Enemy::ChangeState(EnemyPhase phase)
{
}

