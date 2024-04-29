#include "main.h"
#include "manager.h"

#include "input.h"

#include "title.h"

#include "game.h"

#include "shader.h"
#include "sprite.h"

#include "transition.h"

#include "cursor.h"
#include "hpber.h"

#include "stageSelect.h"
#include "camera.h"
#include "player.h"
#include "player2.h"
#include "Tplayer.h"
#include "time.h"
#include "tcamera.h"
#include "field.h"
#include "wall.h"
#include "edit.h"


void Title::Init()
{
	GameObject* titleLogo = AddGameObject<GameObject>(3);			// 3はレイヤ番号
	titleLogo->AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	titleLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT + 50.0f, "asset\\texture\\kaku3.png");

	// チェック完了
	{
		Wall* wall = AddGameObject<Wall>(1);
		wall->SetPosition(DirectX::SimpleMath::Vector3::Vector3(0.0f, -110.0f, 0.0f));
		wall->SetScale(DirectX::SimpleMath::Vector3::Vector3(5.0f, 5.0f, 5.0f));
	}
	// チェック完了
	{
		Field* field = AddGameObject<Field>(1);
		field->SetPosition(DirectX::SimpleMath::Vector3::Vector3(0.0f, -48.0f, 0.0f));
		field->SetScale(DirectX::SimpleMath::Vector3::Vector3(5.0f, 5.0f, 5.0f));
	}

	AddGameObject<TCamera>(0);
	//AddGameObject<Camera>(0);
	AddGameObject<Cursor>(3);
	//AddGameObject<Hpber>(3);

	m_Transition = AddGameObject<Transition>(3);					// 3はレイヤ番号
	m_Transition->FadeIn();
}


void Title::Update()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	// 現在シーンを取得
	Cursor* cursorobj = scene->GetGameObject<Cursor>();
	int sen = cursorobj->GetSen();

	// 
	if (m_Transition->GetState() == Transition::State::Stop) {
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}
	}
	

	// 画面遷移が終了してるか？
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		if (sen == 0) Manager::SetScene<Game>();
		if (sen == 1) Manager::SetScene<Edit>();

		//Manager::SetScene<stageSelect>();
		//Manager::SetScene<>();
	}
}
