#include "Tplayer.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "shader.h"
#include "input.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "bullet.h"
#include "shadow.h"

#include "goal.h"

#include "collision.h"

#include "camera.h"

#include "animationModel.h"

using namespace DirectX::SimpleMath;

void Tplayer::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	m_Model = AddComponent<AnimationModel>();

	m_Model->Load("asset\\model\\Akai2.fbx");									// animation ok
	m_Model->LoadAnimation("asset\\model\\Tidle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Bot_Walk2.fbx", "Walk");
	m_Scale = Vector3(0.3f, 0.3f, 0.3f);
}

void Tplayer::Update()
{
	m_BlendRate -= 0.1f;
	m_Frame++;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;
}

void Tplayer::PreDraw()
{
	m_Model->Update(
		"Idle", m_Frame,
		"Walk", m_Frame,
		m_BlendRate);
}
