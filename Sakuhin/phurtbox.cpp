#include "phurtbox.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"

#include "player.h"

using namespace DirectX::SimpleMath;

void Phurtbox::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\glayobj.obj");
}

void Phurtbox::Update()
{
	Scene* scene = Manager::GetScene();
	Player* playerobj = scene->GetGameObject<Player>();
	Vector3 playerpos = playerobj->GetPosition();

	this->SetPosition(Vector3(playerpos.x + xpos, playerpos.y + ypos, 0.0f));

	this->SetScale(Vector3(ewidth, eheight, 0.1f));
}

void Phurtbox::Set_xpos(float xp)
{
	this->xpos = xp;
}

void Phurtbox::Set_ypos(float yp)
{
	this->ypos = yp;
}

void Phurtbox::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void Phurtbox::Set_eheight(float eh)
{
	this->eheight = eh;
}
