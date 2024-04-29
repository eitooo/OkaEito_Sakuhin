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

// �Q�[����������
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

	// �`�F�b�N����
	{
		Player* player = AddGameObject<Player>(1);
		player->SetPosition(Vector3(-4.5f, 0.0f, 0.0f));
		/*player->SetScale(Vector3(3.0f, 3.0f, 3.0f));*/
	}

	// �`�F�b�N����
	{
		Player2* player2 = AddGameObject<Player2>(1);
		player2->SetPosition(Vector3(4.5f, 0.0f, 0.0f));
	}

	// �`�F�b�N����
	{
		Goal* goal = AddGameObject<Goal>(1);
		goal->SetPosition(Vector3(11.0f, 12.0f, -20.0f));
		goal->SetScale(Vector3(0.5f, 0.5f, 0.5f));
	}

	AddGameObject<Phurtbox>(3);
	AddGameObject<Phitbox>(3);
	AddGameObject<P2hurtbox>(3);
	AddGameObject<P2hitbox>(3);

	// ��ʑJ�ڃI�u�W�F�N�g��o�^
	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();
}

// �Q�[���I������
void Game::Uninit()
{
}

// �Q�[���X�V����
void Game::Update()
{
	// �S�[�����Ă��Ȃ��̂ł����
	if (!m_Goal)
	{
		Goal* goal = GetGameObject<Goal>();

		// �S�[�������ۂɃS�[���I�u�W�F�N�g�͍폜�����
		if (goal == nullptr)
		{
			m_Goal = true;

			// �Q�b��ɃX���b�h�𐶐����ăt�F�[�h�A�E�g�J�n
			Invoke([=]() { m_Transition->FadeOut(); }, 2000);
		}
	}

	// �t�F�[�h�A�E�g���I�����Ă��邩�H
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<Title>();
	}
}
