#define NOMINMAX
#include "WayNode.h"
#include "Model.h"
#include "Manager.h"
#include "window.h"
#include "WayNodeManager.h"

WayNode::WayNode()
{
}


WayNode::~WayNode()
{
}

void WayNode::Init()
{
	model = new Model;
	model->Load("Assets/Models/redbox.fbx");
	model->SetOwner(this);
	componentsList.push_back(model);
	siz = XMFLOAT3(0.01f, 0.01f, 0.01f);
}

void WayNode::Uninit()
{
	if (neighborInfo) {
		delete[] neighborInfo;
	}
}

void WayNode::SetNeighbor(unsigned short* pArray, unsigned short arraySize)
{
	this->arraySize = arraySize;
	Scene* scene = Manager::Get()->GetScene();
	if (scene == nullptr) {
		MessageBox(Manager::Get()->GetWindow()->GethWnd(), "���݃V�[�����擾�ł��܂���ł���", "WayNodeManager", MB_ICONHAND | MB_OK);
		exit(-1);
	}
	WayNodeManager* nodeMgr = scene->GetNodeManager();


	neighborInfo = new WAYNODE_STATUS[arraySize];
	for (int i = 0; i < arraySize; i++) {
		neighborInfo[i].neighborID = pArray[i];
		// ���ׂ����ID�����ɓo�^����Ă���̂Ȃ�A���������߂�
		if (nodeMgr->GetNode(neighborInfo[i].neighborID) != NULL) {
			XMFLOAT3 otherPos = nodeMgr->GetNode(neighborInfo[i].neighborID)->GetPos();
			XMFLOAT3 myPos = GetPos();
			XMVECTOR toOtherVec = XMLoadFloat3(&(otherPos - myPos));
			XMStoreFloat(&neighborInfo[i].length, XMVector3Length(toOtherVec));

			// ����ɁA����ɂ��v�Z���ʂ�͂���
			nodeMgr->GetNode(neighborInfo[i].neighborID)->SetDistance(id, neighborInfo[i].length);

		}
		// ���ׂ��񂪖��o�^��������A-1�����Ă���
		else {
			neighborInfo[i].length = -1;
		}
	}
}

void WayNode::SetDistance(unsigned short id, float length)
{
	for (int i = 0; i < arraySize; i++) {
		if (neighborInfo[i].neighborID == id) {
			neighborInfo[i].length = length;
			return;
		}
	}
	MessageBox(Manager::Get()->GetWindow()->GethWnd(), "�אڃm�[�h�ɋ�����ݒ�ł��܂���B", "�G���[", MB_ICONHAND | MB_OK);
	exit(-1);
}

void WayNode::SetID(unsigned short myID)
{
	id = myID;
}

unsigned short WayNode::GetID()
{
	return id;
}


