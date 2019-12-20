#include "Model.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"


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
	model->Load("Assets/Models/human.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);
	input = Manager::Get()->GetInput();
	//Camera* camera = Manager::Get()->GetScene()->GetGameObject<Camera>(e_LAYER_CAMERA);
	//camera->SetOwner(this);
	scene = Manager::Get()->GetScene();
}

//void Player::Uninit()
//{

//}

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



	if (input->GetKeyPress('A')) {
		rot.y += 0.1f;
	}




}
