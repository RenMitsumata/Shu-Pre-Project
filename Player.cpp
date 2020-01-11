#include "Model.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "CollisionSphere.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/SambaDancing2.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);

	
	CollisionSphere* col = ComponentFactory::CreateComponent<CollisionSphere>();
	col->SetRadius(1.0f);
	col->SetTag(e_COLTYPE_PLAYER);
	col->SetOwner(this);
	componentsList.push_back(col);
	
	
	input = Manager::Get()->GetInput();
	//Camera* camera = Manager::Get()->GetScene()->GetGameObject<Camera>(e_LAYER_CAMERA);
	//camera->SetOwner(this);
	scene = Manager::Get()->GetScene();
}


void Player::Update()
{
	

	if (input->GetKeyPress(VK_UP)) {
		pos.z += 0.1f;
	}
	if (input->GetKeyPress(VK_DOWN)) {
		pos.z -= 0.1f;
	}
	if (input->GetKeyPress(VK_LEFT)) {
		pos.x -= 0.1f;
	}
	if (input->GetKeyPress(VK_RIGHT)) {
		pos.x += 0.1f;
	}
	if (input->GetKeyPress(VK_LSHIFT)) {
		pos.y += 0.1f;
	}
	if (input->GetKeyPress(VK_RSHIFT)) {
		pos.y -= 0.1f;
	}
	if (input->GetKeyTrigger(VK_SPACE)) {
		Bullet* bullet = scene->AddGameObject<Bullet>(e_LAYER_GAMEOBJECT);
		bullet->SetPos(pos);
		bullet->SetRot(rot);
		
		bullet->SetVelocity(front * 0.5f);
	}
}
