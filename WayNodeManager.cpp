#include "WayNodeManager.h"
#include "WayNode.h"
#include "Manager.h"
#include "window.h"
#include <iterator>

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
		MessageBox(Manager::Get()->GetWindow()->GethWnd(), "ノードIDが重複しています", "ノード登録エラー", MB_ICONHAND | MB_OK);
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

unsigned short WayNodeManager::FindDestNode(XMFLOAT3 pos)
{
	unsigned short dest = 0xFFFF;
	float dist = 5.0f;

	//　一定距離内のノードを検索
	while (dest == 0xFFFF) {
		// 連想配列を先頭から検索
		std::unordered_map<unsigned short, WayNode*>::iterator itr = NodeList.begin();
		WayNode* way = itr->second;
		XMFLOAT3 posNode = way->GetPos();
		float length;
		XMStoreFloat(&length, XMVector3Length(XMLoadFloat3(&pos) - XMLoadFloat3(&posNode)));
		if (length < dist) {

		}


	}
	return dest;
}
