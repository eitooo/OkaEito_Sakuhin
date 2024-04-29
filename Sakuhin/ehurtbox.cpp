#include "ehurtbox.h"

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "EPlayer.h"

using namespace DirectX::SimpleMath;

void Ehurtbox::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	//AddComponent<Sprite>()->Init(760.0f, 30.0f, NowHp / MaxHp * 500.0f , 40.0f, "asset\\texture\\hpg.png");

	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"asset/texture/yuka.png",
		nullptr,
		&m_Texture);

	assert(m_Texture);
}

void Ehurtbox::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void Ehurtbox::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));

	material.Diffuse = Color(0.5f, 0.3f, 0.3f, 0.3f);

	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	Scene* scene = Manager::GetScene();
	EPlayer* playerobj = scene->GetGameObject<EPlayer>();

	//Vector3 p_position = playerobj->GetPosition();
	Vector3 p_position = playerobj->GetPosition();

	float x_p = 650.0f;
	float y_p = 420.0f;

	vertex[0].Position = Vector3(p_position.x + this->xpos - (this->ewidth / 2) + x_p, p_position.y + this->ypos - (this->eheight / 2) + y_p, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(1.0f, 1.0f);

	vertex[1].Position = Vector3(p_position.x + this->xpos + (this->ewidth / 2) + x_p, p_position.y + this->ypos - (this->eheight / 2) + y_p, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 1.0f);

	vertex[2].Position = Vector3(p_position.x + this->xpos - (this->ewidth / 2) + x_p, p_position.y + this->ypos + (this->eheight / 2) + y_p, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(1.0f, 1.0f);

	vertex[3].Position = Vector3(p_position.x + this->xpos + (this->ewidth / 2) + x_p, p_position.y + this->ypos + (this->eheight / 2) + y_p, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Ehurtbox::Update()
{
}

void Ehurtbox::Set_xpos(float xp)
{
	this->xpos = xp;
}

void Ehurtbox::Set_ypos(float yp)
{
	this->ypos = yp;
}

void Ehurtbox::Set_ewidth(float ew)
{
	this->ewidth = ew;
}

void Ehurtbox::Set_eheight(float eh)
{
	this->eheight = eh;
}
