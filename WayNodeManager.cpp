#include "WayNodeManager.h"
#include "WayNode.h"
#include "Manager.h"
#include "window.h"

WayNodeManager::WayNodeManager()
{
}


WayNodeManager::~WayNodeManager()
{
}

void WayNodeManager::Init()
{
}

void WayNodeManager::Uninit()
{
}

void WayNodeManager::AddList(WayNode* node)
{
	unsigned short id = node->GetID();
	if (NodeList[id] != nullptr) {
		MessageBox(Manager::Get()->GetWindow()->GethWnd(), "�m�[�hID���d�����Ă��܂�", "�m�[�h�o�^�G���[", MB_ICONHAND | MB_OK);
		exit(-1);
	}
	NodeList[id] = node;
}

WayNode* WayNodeManager::GetNode(unsigned short id)
{
	if (NodeList[id]) {
		return NodeList[id];
	}
	else return nullptr;
}
