#include "ecamera.h"
#include "EPlayer.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"

using namespace DirectX::SimpleMath;

void ECamera::Init()
{
	m_Position = Vector3(0.0f, 1.0f, -90.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

void ECamera::Uninit()
{
}

void ECamera::Update()
{
	Scene* nowscene = Manager::GetScene();
	EPlayer* playerobj = nowscene->GetGameObject<EPlayer>();

	Vector3 playerpos = playerobj->GetPosition();
	this->m_Position = Vector3(0.0f, 3.0f, playerpos.z + 10.0f);
	this->m_Target = Vector3(playerpos.x, 3.0f, 0.0f);
}

void ECamera::Draw()
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
