#include "WayNodeManager.h"
#include "WayNode.h"
#include "Manager.h"
#include "window.h"
#include <iterator>
#include <algorithm>


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

unsigned short WayNodeManager::FindDestNode(XMFLOAT3 pos)
{
	unsigned short dest = 0xFFFF;	// �Ԃ��m�[�h�h�c
	float shortest_length = 5.0f;	// �ŋ߃m�[�h�܂ł̋���

	//�@��苗�����̃m�[�h������
	
	for (std::unordered_map<unsigned short, WayNode*>::iterator itr = NodeList.begin(); itr != NodeList.end(); itr++) {
		// �A�z�z���擪���猟��
		WayNode* way = itr->second;
		XMFLOAT3 posNode = way->GetPos();
		float length;
		XMStoreFloat(&length, XMVector3Length(XMLoadFloat3(&pos) - XMLoadFloat3(&posNode)));
		if (length < shortest_length) {
			dest = way->GetID();
			shortest_length = length;
		}
	}
	
	
	return dest;
}

std::vector<unsigned short> WayNodeManager::FindAStar(XMFLOAT3 destPos, XMFLOAT3 myPos)
{
	// �����̃��Z�b�g
	routeList.clear();

	// �����̎��߃m�[�h�����߂�
	unsigned short myID = FindDestNode(myPos);

	// �ړI�n�̎��߃m�[�h�����߂�
	unsigned short destID = FindDestNode(destPos);

	// �o�H�T��������
	CanReach(myID, destID);

	return routeList;

}

bool WayNodeManager::CanReach(unsigned short curID, unsigned short destID)
{
	routeList.push_back(curID);

	NEIGHBOR_INFO neighbors = NodeList[curID]->GetNeighborInfo();
	
	std::vector<WAYNODE_STATUS> waynodeList;

	for (int i = 0; i < neighbors.num; i++) {
		WAYNODE_STATUS waynode;
		waynode.neighborID = neighbors.neighborInfo[i].neighborID;
		waynode.length = CalcDistance(neighbors.neighborInfo[i].neighborID, destID);
		waynodeList.push_back(waynode);
	}
	
	// �ړI�n�ւ̋������߂��m�[�h���ɕ��ёւ�
	std::sort(waynodeList.begin(), waynodeList.end(), [](WAYNODE_STATUS x, WAYNODE_STATUS y) {return x.length < y.length; });
	



	for (int i = 0; i < neighbors.num; i++) {
		
		// ��x�ʂ����m�[�h�͒ʂ�Ȃ�
		bool isOncePassed = false;

		for (auto t : routeList) {
			if (waynodeList[i].neighborID == t) {
				isOncePassed = true;
				break;
			}
		}

		if (isOncePassed) {
			continue;
		}
		

		// destID�ƈ�v����Ȃ�A���B�������ƂɂȂ�
		if (waynodeList[i].neighborID == destID) {
			return true;
		}

		// �܂��ʂ��Ă��Ȃ��m�[�h�̏ꍇ�A����ɐ�𒲂ׂ�(�ړI�n�ւ̋������߂���)
		bool isReach = CanReach(waynodeList[i].neighborID, destID);

		if (isReach) {
			return true;
		}		
	}

	// ���̃m�[�h����͓��B�ł��Ȃ�����
	routeList.pop_back();
	return false;
}

float WayNodeManager::CalcDistance(unsigned short startID, unsigned short destID)
{
	XMFLOAT3 startpos = NodeList[startID]->GetPos();
	XMFLOAT3 destpos = NodeList[destID]->GetPos();
	XMVECTOR lengthVec = XMVector3Length(XMLoadFloat3(&destpos) - XMLoadFloat3(&startpos));
	float ret;
	XMStoreFloat(&ret, lengthVec);
	return ret;
}
