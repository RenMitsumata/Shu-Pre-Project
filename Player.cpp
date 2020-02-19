#include "Model.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "CollisionCone.h"
#include "AudioManager.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	rot = XMFLOAT3(0.0f, XMConvertToRadians(180.0f), 0.0f);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
	front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	
	
	

	Model* model = ComponentFactory::CreateComponent<Model>();
	model->Load("Assets/Models/human2.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);

	CollisionCapsule* col = ComponentFactory::CreateComponent<CollisionCapsule>();
	col->SetParams(1.5f, 0.6f);
	col->SetDeltaPos(XMFLOAT3(0.0f, 1.0f, 0.0f));
	col->SetTag(e_COLTYPE_PLAYER);
	col->SetOwner(this);
	componentsList.push_back(col);

	/*
	CollisionCone* cone = ComponentFactory::CreateComponent<CollisionCone>();
	cone->SetParams(0.3f, 1.0f, 3.0f);
	cone->SetDeltaPos(XMFLOAT3(0.0f, 2.0f, 0.0f));
	cone->SetOwner(this);
	componentsList.push_back(cone);
	*/
	
	input = Manager::Get()->GetInput();

	
	Camera* camera = Manager::Get()->GetScene()->AddGameObject<Camera>(e_LAYER_CAMERA);
	camera->SetDeltaPos(XMFLOAT3(-1.0f, 2.0f, 2.5f));
	camera->SetDeltaRot(XMFLOAT3(0.0f, 0.0f, 0.0f));
	camera->SetOwner(this);
	
	scene = Manager::Get()->GetScene();
	audio = Manager::Get()->GetAudio();
	soundMap["shoot"] = audio->Load("Assets/Sounds/shoot.wav");
}


void Player::Update()
{
	

	if (input->GetKeyPress('W')) {
		//pos.z += 0.1f;
		AddPos(front * 0.1f);
	}
	if (input->GetKeyPress('S')) {
		//pos.z -= 0.1f;
		AddPos(front * -0.1f);
	}
	if (input->GetKeyPress('A')) {
		XMVECTOR upVec = XMLoadFloat3(&up);
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMFLOAT3 right;
		XMStoreFloat3(&right, XMVector3Cross(upVec, frontVec));
		AddPos(right * -0.1f);
	}
	if (input->GetKeyPress('D')) {
		XMVECTOR upVec = XMLoadFloat3(&up);
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMFLOAT3 right;
		XMStoreFloat3(&right, XMVector3Cross(upVec, frontVec));
		AddPos(right * 0.1f);
	}

	if (input->GetKeyPress(VK_LEFT)) {
		AddRot(XMFLOAT3(0.0f,-0.05f,0.0f));
	}

	if (input->GetKeyPress(VK_RIGHT)) {
		AddRot(XMFLOAT3(0.0f, 0.05f, 0.0f));
	}






	/*
	if (input->GetKeyPress(VK_LSHIFT)) {
		pos.y += 0.1f;
	}
	if (input->GetKeyPress(VK_RSHIFT)) {
		pos.y -= 0.1f;
	}
	*/
	if (input->GetKeyTrigger(VK_SPACE)) {
		Bullet* bullet = scene->AddGameObject<Bullet>(e_LAYER_GAMEOBJECT);
		bullet->SetPos(pos);
		bullet->SetRot(rot);
		
		bullet->SetVelocity(front * 0.5f);
		audio->Play(soundMap["shoot"]);
	}
}
