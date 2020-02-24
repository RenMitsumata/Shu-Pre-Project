#include "ImpactSound.h"
#include "CollisionSphere.h"


ImpactSound::ImpactSound()
{
}


ImpactSound::~ImpactSound()
{
}

void ImpactSound::Init()
{
	CollisionSphere* col = ComponentFactory::CreateComponent<CollisionSphere>();
	col->SetRadius(10.0f);
	col->SetTag(e_COLTYPE_SOUND);
}

void ImpactSound::Update()
{
	SetDestroy();
}
