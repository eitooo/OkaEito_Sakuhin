#include "p2hitbox.h"
#include "shader.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "player2.h"

using namespace DirectX::SimpleMath;

void P2hitbox::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\redbox.obj");
}

void P2hitbox::Update()
{
	Scene* scene = Manager::GetScene();
	Player2* playerobj = scene->GetGameObject<Player2>();
	Vector3 playerpos = playerobj->GetPosition();

	this->SetPosition(Vector3(playerpos.x - xpos, playerpos.y + ypos, 0.0f));

	this->SetScale(Vector3(ewidth, eheight, 0.1f));
}

void P2hitbox::Set_xpos(float xp)
{
	this->xpos = xp;
}

void P2hitbox::Set_ypos(float yp)
{
	this->ypos = yp;
}

void P2hitbox::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void P2hitbox::Set_eheight(float eh)
{
	this->eheight = eh;
}
