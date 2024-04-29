#include "phitbox.h"
#include "shader.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

using namespace DirectX::SimpleMath;

void Phitbox::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\redbox.obj");
}

void Phitbox::Update()
{
	Scene* scene = Manager::GetScene();
	Player* playerobj = scene->GetGameObject<Player>();
	Vector3 playerpos = playerobj->GetPosition();

	this->SetPosition(Vector3(playerpos.x + xpos, playerpos.y + ypos, 0.0f));

	this->SetScale(Vector3(ewidth, eheight, 0.1f));
}

void Phitbox::Set_xpos(float xp)
{
	this->xpos = xp;
}

void Phitbox::Set_ypos(float yp)
{
	this->ypos = yp;
}

void Phitbox::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void Phitbox::Set_eheight(float eh)
{
	this->eheight = eh;
}
