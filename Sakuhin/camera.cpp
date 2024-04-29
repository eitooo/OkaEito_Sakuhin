#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "player2.h"

using namespace DirectX::SimpleMath;

void Camera::Init()
{
	m_Position = Vector3(0.0f, 1.0f, -90.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
	Scene* nowscene = Manager::GetScene();
	Player* playerobj = nowscene->GetGameObject<Player>();
	Player2* player2obj = nowscene->GetGameObject<Player2>();

	//Vector3 forward = playerobj->GetForward();
	//Vector3 playerpos = playerobj->GetPosition();

	//Matrix rotMx = Matrix::CreateRotationY(90.0f / 180.0f * 3.14159265358979323865f);
	//Vector3 right = Vector3::Transform(forward, rotMx);
	//this->m_Position = playerpos + right * 13.0f;
	//this->m_Target = playerpos + Vector3(5.0f,3.2f,0.0f);// +forward * 7.0f;
	//this->m_Target.y = 3.2f;
	//this->m_Position.y = 1.0f;

	/*Vector3 forward = playerobj->GetForward();*/
	Vector3 playerpos = playerobj->GetPosition();
	Vector3 player2pos = player2obj->GetPosition();

	float playerdis = (playerpos.x + player2pos.x) / 2.0f;
	this->m_Position = Vector3(playerdis, 3.0f, -10.0f);
	this->m_Target = Vector3(playerdis, 3.0f, 0.0f);

	float movelimit = 4.0f;

	if (m_Position.x > movelimit) {
		m_Position.x = movelimit;
	}
	if (m_Position.x < -movelimit) {
		m_Position.x = -movelimit;
	}

	if (m_Target.x > movelimit) {
		m_Target.x = movelimit;
	}
	if (m_Target.x < -movelimit) {
		m_Target.x = -movelimit;
	}

}

void Camera::Draw()
{
	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);										// ����n�ɂ����@20230511 by suzuki.tomoki

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);	// �A�X�y�N�g��	
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// ����n�ɂ����@20230511 by suzuki.tomoki

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}