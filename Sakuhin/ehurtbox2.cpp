#include "ehurtbox2.h"
#include "shader.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "EPlayer.h"

using namespace DirectX::SimpleMath;

void Ehurtbox2::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\glayobj.obj");
}

void Ehurtbox2::Update()
{
	Scene* scene = Manager::GetScene();
	EPlayer* playerobj = scene->GetGameObject<EPlayer>();
	Vector3 playerpos = playerobj->GetPosition();

	this->SetPosition(Vector3(playerpos.x - xpos, playerpos.y + ypos, -0.52f));

	this->SetScale(Vector3(ewidth, eheight, 0.1f));
}

void Ehurtbox2::Set_xpos(float xp)
{
	this->xpos = xp;
}

void Ehurtbox2::Set_ypos(float yp)
{
	this->ypos = yp;
}

void Ehurtbox2::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void Ehurtbox2::Set_eheight(float eh)
{
	this->eheight = eh;
}
