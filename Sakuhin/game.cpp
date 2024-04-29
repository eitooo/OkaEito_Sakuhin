#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "camera.h"
#include "field.h"
#include "wall.h"
#include "player.h"
#include "player2.h"

#include "game.h"
#include "input.h"
#include "audio.h"
#include "Polygon2D.h"

#include "manager.h"
#include "transition.h"

#include "result.h"

#include "goal.h"

#include "utility.h"

#include "score.h"

#include "explosion.h"

#include "Time.h"

#include "hpcover.h"
#include "hpber.h"
#include "hpber2.h"

#include "stageSelect.h"
#include "title.h"
#include "phurtbox.h"
#include "phitbox.h"
#include "p2hurtbox.h"
#include "p2hitbox.h"
#include "Combo.h"
#include "Combo2.h"

using namespace DirectX::SimpleMath;

// ゲーム初期処理
void Game::Init()
{
	AddGameObject<Camera>(0);

	AddGameObject<Field>(1);
	AddGameObject<Wall>(1);

	AddGameObject<Time>(3);
	AddGameObject<Hpber>(3);
	AddGameObject<HPber2>(3);
	AddGameObject<Combo>(3);
	AddGameObject<Combo2>(3);

	// チェック完了
	{
		Player* player = AddGameObject<Player>(1);
		player->SetPosition(Vector3(-4.5f, 0.0f, 0.0f));
		/*player->SetScale(Vector3(3.0f, 3.0f, 3.0f));*/
	}

	// チェック完了
	{
		Player2* player2 = AddGameObject<Player2>(1);
		player2->SetPosition(Vector3(4.5f, 0.0f, 0.0f));
	}

	// チェック完了
	{
		Goal* goal = AddGameObject<Goal>(1);
		goal->SetPosition(Vector3(11.0f, 12.0f, -20.0f));
		goal->SetScale(Vector3(0.5f, 0.5f, 0.5f));
	}

	AddGameObject<Phurtbox>(3);
	AddGameObject<Phitbox>(3);
	AddGameObject<P2hurtbox>(3);
	AddGameObject<P2hitbox>(3);

	// 画面遷移オブジェクトを登録
	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();
}

// ゲーム終了処理
void Game::Uninit()
{
}

// ゲーム更新処理
void Game::Update()
{
	// ゴールしていないのであれば
	if (!m_Goal)
	{
		Goal* goal = GetGameObject<Goal>();

		// ゴールした際にゴールオブジェクトは削除される
		if (goal == nullptr)
		{
			m_Goal = true;

			// ２秒後にスレッドを生成してフェードアウト開始
			Invoke([=]() { m_Transition->FadeOut(); }, 2000);
		}
	}

	// フェードアウトが終了しているか？
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<Title>();
	}
}
