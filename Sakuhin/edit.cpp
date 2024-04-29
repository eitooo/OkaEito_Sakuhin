#include "edit.h"
#include "imgui/imgui.h"
#include "field.h"
#include "wall.h"
#include "EPlayer.h"
#include "ecamera.h"
#include "renderer.h"
#include "time.h"
#include "ehitbox2.h"
#include "ehurtbox2.h"

using namespace DirectX::SimpleMath;

void Edit::Init()
{
	AddGameObject<ECamera>(0);

	// チェック完了
	{
		EPlayer* player = AddGameObject<EPlayer>(1);
		player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		player->SetRotation(Vector3(0.0f, -1.5f, 0.0f));
	}

	// チェック完了
	{
		Ehurtbox2* hurtbox = AddGameObject<Ehurtbox2>(1);
		hurtbox->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}

	// チェック完了
	{
		Ehitbox2* hitbox = AddGameObject<Ehitbox2>(1);
		hitbox->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}	
}

void Edit::Uninit()
{
}

void Edit::Update()
{
}

void Edit::Draw()
{
	auto player = GetGameObject<EPlayer>();
	player->ShowDebugWindow();
}
