#include "hpcover.h"

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "shader.h"
#include "sprite.h"

void HPcover::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Sprite>()->Init(730.0f, 10.0f, 550.0f, 70.0f, "asset\\texture\\hpc2.png");
	AddComponent<Sprite>()->Init(0.0f, 10.0f, 550.0f, 70.0f, "asset\\texture\\hpc3.png");
}

void HPcover::Uninit()
{
}

void HPcover::Update()
{
	/*float i = 550.0f;

	Maxhp += 0.1f;
	AddComponent<Sprite>()->Init(730.0f, 10.0f, Maxhp, 50.0f, "asset\\texture\\hpg.png");
	SetDestroy();*/
}
