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
	// ビュー変換後列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);										// 左手系にした　20230511 by suzuki.tomoki

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);	// アスペクト比	
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//プロジェクション行列の生成
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// 左手系にした　20230511 by suzuki.tomoki

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}