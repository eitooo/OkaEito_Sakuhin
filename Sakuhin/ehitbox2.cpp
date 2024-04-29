#include "ehitbox2.h"
#include "shader.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "EPlayer.h"

using namespace DirectX::SimpleMath;

void Ehitbox2::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\redbox.obj");
}

void Ehitbox2::Update()
{
	Scene* scene = Manager::GetScene();
	EPlayer* playerobj = scene->GetGameObject<EPlayer>();
	Vector3 playerpos = playerobj->GetPosition();

	this->SetPosition(Vector3(playerpos.x - xpos, playerpos.y + ypos,-0.5f));

	this->SetScale(Vector3(ewidth, eheight, 0.1f));
}

void Ehitbox2::Set_xpos(float xp)
{
	this->xpos = xp;
}

void Ehitbox2::Set_ypos(float yp)
{
	this->ypos = yp;
}

void Ehitbox2::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void Ehitbox2::Set_eheight(float eh)
{
	this->eheight = eh;
}
