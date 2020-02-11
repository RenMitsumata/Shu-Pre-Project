#include "Title.h"
#include "Manager.h"
#include "InputManager.h"
#include "UI.h"
#include "Game.h"


Title::Title()
{
}


Title::~Title()
{
}

void Title::Init()
{
	UI* ui = AddGameObject<UI>(e_LAYER_UI);
	ui->SetTextureAndSize("Assets/Textures/t_title001.png");
	input = Manager::Get()->GetInput();
}

void Title::Update()
{
	if (input->GetKeyTrigger(VK_SPACE)) {
		Manager::Get()->ChangeScene(new Game);
	}
}
