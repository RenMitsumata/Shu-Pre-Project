#include "MapManager.h"
#include <io.h>
#include "Manager.h"
#include "Scene.h"
#include <string>
#include "Wall.h"
#include "WayNode.h"
#include "WayNodeManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Floor.h"

MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

void MapManager::Init()
{
}

void MapManager::Uninit()
{
}

void MapManager::ReadMap(const char* filename)
{
	Scene* scene = Manager::Get()->GetScene();
	WayNodeManager* nodeMgr = scene->GetNodeManager();

	// �}�b�v�f�[�^�̏����Ă���t�@�C����ǂݍ���
	FILE* fp;
	long fileSize;
	fp = fopen(filename, "rt");
	fileSize = _filelength(_fileno(fp));
	
	// �o�b�t�@�ɏ�������
	unsigned char* buffer = new unsigned char[fileSize];
	for (int i = 0; i < fileSize; i++) {
		buffer[i] = fgetc(fp);
	}

	// �t�@�C�������
	fclose(fp);
	
	// �ǂݍ��񂾃f�[�^�����
	char currentData = buffer[0];
	unsigned int currentPoint = 0;

	// �J�����������܂œǂݔ�΂�
	while (currentPoint < fileSize) {
		while (currentData != '{') {
			currentPoint++;
			currentData = buffer[currentPoint];
			if (currentPoint >= fileSize) {
				return;
			}
		}		

		while (currentData != ':') {
			currentPoint++;
			currentData = buffer[currentPoint];
		}
		// ���ʎq�𔻒�
		char identity[24];
		unsigned char iNum = 0;
		while (currentData != ';') {
			currentPoint++;
			currentData = buffer[currentPoint];
			identity[iNum] = currentData;
			iNum++;
		}
		std::string idName(identity,iNum - 1);

		
		if (idName == "WALL") {
			// �����ɕK�v�ȃ����o
			XMFLOAT3 pos;
			XMFLOAT3 rot;
			XMFLOAT3 siz;
			float posMem[3];
			char locBuffer[64];
			unsigned char locCnt = 0;


			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}


			// �|�W�V�������擾
			
			for (int i = 0; i < 3; i++) {
				
				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;
				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];
				}
				
				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			pos = { posMem[0],posMem[1],posMem[2] };

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			// ��]���擾
			ZeroMemory(posMem, sizeof(float) * 3);
			for (int i = 0; i < 3; i++) {

				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;

				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];
					
				}
			
				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			rot = { XMConvertToRadians(posMem[0]),XMConvertToRadians(posMem[1]),XMConvertToRadians(posMem[2]) };

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			// �T�C�Y���擾
			ZeroMemory(posMem, sizeof(float) * 3);
			for (int i = 0; i < 3; i++) {

				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;

				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];					
				}
				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			siz = { posMem[0] * 0.01f,posMem[1] * 0.01f,posMem[2] * 0.01f };
			Wall* wall = scene->AddGameObject<Wall>(e_LAYER_GAMEOBJECT);
			wall->SetPos(pos);
			wall->SetRot(rot);
			wall->SetSiz(siz);
		} // if(WALL)
			
		if (idName == "NODE"){
			// �����ɕK�v�ȃ����o
			XMFLOAT3 pos;
			unsigned short id;
			unsigned short neighbor[16];
			float posMem[3];
			char locBuffer[64];
			unsigned char locCnt = 0;

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}


			// �|�W�V�������擾

			for (int i = 0; i < 3; i++) {

				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;
				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];
				}

				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			pos = { posMem[0],posMem[1],posMem[2] };

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			// ID���擾
			currentPoint++;
			currentData = buffer[currentPoint];
			locCnt = 0;
			while (currentData != ';') {				
				locBuffer[locCnt] = currentData;
				locCnt++;
				currentPoint++;
				currentData = buffer[currentPoint];
			}
			id = atof(locBuffer);
			ZeroMemory(locBuffer, 64);
			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			// �ׂ̃m�[�h���o�^�y�ы����v�Z
			unsigned char neighborCnt = 1;
			locCnt = 0;
			currentPoint++;
			currentData = buffer[currentPoint];
			while (currentData != ';') {
				if (currentData == ',') {
					neighborCnt++;
				}
				locBuffer[locCnt] = currentData;
				locCnt++;
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			unsigned short* neighborArray = new unsigned short[neighborCnt];
			char* pBuf = locBuffer;
			char neighborID[6];
			unsigned char itr = 0;

			

			while (*pBuf != '\0') {
				unsigned char neighborIDPos = 0;
				ZeroMemory(neighborID, sizeof(char) * 6);
				while (*pBuf != ',' && neighborIDPos < 6) {
					neighborID[neighborIDPos] = *pBuf;
					neighborIDPos++;
					pBuf++;
				}
				neighborArray[itr] = atoi(neighborID);				
				pBuf++;
				itr++;
			}

			WayNode* node = scene->AddGameObject<WayNode>(e_LAYER_GAMEOBJECT);

			node->SetPos(pos);
			node->SetID(id);
			node->SetNeighbor(neighborArray, neighborCnt);
			nodeMgr->AddList(node);
			delete[] neighborArray;
		} //if(NODE)
			
		if (idName == "ENEMY") {
			// �����ɕK�v�ȃ����o
			XMFLOAT3 pos;
			unsigned short* nodeArray;
			float posMem[3];
			char locBuffer[64];
			unsigned char locCnt = 0;

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}


			// �|�W�V�������擾

			for (int i = 0; i < 3; i++) {

				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;
				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];
				}

				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			pos = { posMem[0],posMem[1],posMem[2] };

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			// �ׂ̃m�[�h���o�^�y�ы����v�Z
			unsigned char nodeCnt = 1;
			locCnt = 0;
			currentPoint++;
			currentData = buffer[currentPoint];
			while (currentData != ';') {
				if (currentData == ',') {
					nodeCnt++;
				}
				locBuffer[locCnt] = currentData;
				locCnt++;
				currentPoint++;
				currentData = buffer[currentPoint];
			}

			nodeArray = new unsigned short[nodeCnt];
			char* pBuf = locBuffer;
			char nodeID[6];
			unsigned char itr = 0;



			while (*pBuf != '\0') {
				unsigned char nodeIDPos = 0;
				ZeroMemory(nodeID, sizeof(char) * 6);
				while (*pBuf != ',' && nodeIDPos < 6) {
					nodeID[nodeIDPos] = *pBuf;
					nodeIDPos++;
					pBuf++;
				}
				nodeArray[itr] = atoi(nodeID);
				pBuf++;
				itr++;
			}

			Enemy* enemy = scene->AddGameObject<Enemy>(e_LAYER_GAMEOBJECT);
			enemy->SetPos(pos);
			enemy->SetWanderNode(nodeArray, nodeCnt);

			delete[] nodeArray;



		}// if(ENEMY)

		if (idName == "PLAYER") {
			Player* player = scene->AddGameObject<Player>(e_LAYER_GAMEOBJECT);
		}

		if (idName == "FLOOR") {
			// �����ɕK�v�ȃ����o
			XMFLOAT3 pos;
			float posMem[3];
			char locBuffer[64];
			unsigned char locCnt = 0;

			// ����:�܂œǂݔ�΂�
			while (currentData != ':') {
				currentPoint++;
				currentData = buffer[currentPoint];
			}


			// �|�W�V�������擾

			for (int i = 0; i < 3; i++) {

				currentPoint++;
				currentData = buffer[currentPoint];
				locCnt = 0;
				while (currentData != ',' && currentData != ';') {
					locBuffer[locCnt] = currentData;
					locCnt++;
					currentPoint++;
					currentData = buffer[currentPoint];
				}

				posMem[i] = atof(locBuffer);
				ZeroMemory(locBuffer, 64);
			}
			pos = { posMem[0],posMem[1],posMem[2] };

			Floor* floor = scene->AddGameObject<Floor>(e_LAYER_BACKGROUND);
			floor->SetPos(pos);

		}

	} // while(currentPoint < fileSize) 

	
}
