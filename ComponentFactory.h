#pragma once




// �O���錾
class Model;
class CollisionOBB;
class CollisionSphere;

class ComponentFactory
{
public:
	enum ComponentType {
		e_Component_Model,
		// �R���|�[�l���g�̎�ނ�ǉ�
	};

	ComponentFactory();
	~ComponentFactory();

	template <class T>
	static T* CreateComponent(){
		T* comp = new T;
		comp->Init();
		return comp;
	}
};

