#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "shader.h"
#include "player.h"
#include "player2.h"
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

#include <math.h>

#include "p2hurtbox.h"
#include "p2hitbox.h"

using namespace DirectX::SimpleMath;

void Player2::Init()
{
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<Shader>()->Load("shader\\vertexLightingOneSkinVS.cso", "shader\\vertexLightingPS.cso"); //20230909-02

	m_Model = AddComponent<AnimationModel>();

	m_Model->Load("asset\\model\\Akai2.fbx");				// animation ok
	m_Model->LoadAnimation("asset\\model\\Bot_Idle2.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Bot_Walk2.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\Bot_Jump2.fbx", "Jump");
	m_Model->LoadAnimation("asset\\model\\Bot_Crouchi2.fbx", "Crouchi");
	m_Model->LoadAnimation("asset\\model\\Light_Attack.fbx", "Light_Attack");
	m_Model->LoadAnimation("asset\\model\\Medium_Attack.fbx", "Medium_Attack");
	m_Model->LoadAnimation("asset\\model\\Heavy_Attack.fbx", "Heavy_Attack");
	m_Model->LoadAnimation("asset\\model\\Jump_Attack.fbx", "Jump_Attack");
	m_Model->LoadAnimation("asset\\model\\SP_Attack.fbx", "SP_Attack");
	m_Model->LoadAnimation("asset\\model\\Hit.fbx", "Hit");
	m_Model->LoadAnimation("asset\\model\\Down.fbx", "CriticalHit");
	m_Model->LoadAnimation("asset\\model\\Dying.fbx", "Dying");
	m_Model->LoadAnimation("asset\\model\\win.fbx", "Win");
	m_Model->LoadAnimation("asset\\model\\Block2.fbx", "Guard");
	m_Model->LoadAnimation("asset\\model\\Grap_ready.fbx", "Grap_ready");
	m_Model->LoadAnimation("asset\\model\\Grap_motion.fbx", "Grap_motion");

	AddComponent<Shadow>()->SetSize(1.5f);

	m_SE = AddComponent<Audio>();
	m_SE->Load("asset\\audio\\wan.wav");

	m_Scale = Vector3(0.03f, 0.03f, 0.03f);

	//ファイルからのデータを格納する
	double ld[MaxN] = { 0.0 };
	double md[MaxN] = { 0.0 };
	double hd[MaxN] = { 0.0 };
	double id[MaxN] = { 0.0 };
	double cd[MaxN] = { 0.0 };
	double wd[MaxN] = { 0.0 };
	double jd[MaxN] = { 0.0 };
	double grd[MaxN] = { 0.0 };
	double flmd[MaxN] = { 0.0 };

	int i;
	FILE* fp1;

	//IDLEデータ読み込み
	fopen_s(&fp1, "data\\IDLE_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &id[i]) != EOF) {
		i++;
	}

	for (int i = 0; i < IDLEFlame; i++)
	{
		idle_data[i].hurtbox1_x_pos = id[2 + (9 * i)];
		idle_data[i].hurtbox1_y_pos = id[3 + (9 * i)];
		idle_data[i].hurtbox1_height_s = id[4 + (9 * i)];
		idle_data[i].hurtbox1_width_s = id[5 + (9 * i)];
				  
		idle_data[i].hitbox1_x_pos = id[6 + (9 * i)];
		idle_data[i].hitbox1_y_pos = id[7 + (9 * i)];
		idle_data[i].hitbox1_height_s = id[8 + (9 * i)];
		idle_data[i].hitbox1_width_s = id[9 + (9 * i)];
	}

	fclose(fp1);

	//CROUCHIデータ読み込み
	fopen_s(&fp1, "data\\CROUCHI_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &cd[i]) != EOF) {
		i++;
	}

	for (int i = 0; i < CROUCHIFlame; i++)
	{
		crouchi_data[i].hurtbox1_x_pos = cd[2 + (9 * i)];
		crouchi_data[i].hurtbox1_y_pos = cd[3 + (9 * i)];
		crouchi_data[i].hurtbox1_height_s = cd[4 + (9 * i)];
		crouchi_data[i].hurtbox1_width_s = cd[5 + (9 * i)];

		crouchi_data[i].hitbox1_x_pos = cd[6 + (9 * i)];
		crouchi_data[i].hitbox1_y_pos = cd[7 + (9 * i)];
		crouchi_data[i].hitbox1_height_s = cd[8 + (9 * i)];
		crouchi_data[i].hitbox1_width_s = cd[9 + (9 * i)];
	}

	fclose(fp1);

	//WALKデータ読み込み
	fopen_s(&fp1, "data\\WALK_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &wd[i]) != EOF) {
		i++;
	}

	for (int i = 0; i < WALKFlame; i++)
	{
		walk_data[i].hurtbox1_x_pos = wd[2 + (9 * i)];
		walk_data[i].hurtbox1_y_pos = wd[3 + (9 * i)];
		walk_data[i].hurtbox1_height_s = wd[4 + (9 * i)];
		walk_data[i].hurtbox1_width_s = wd[5 + (9 * i)];
		
		walk_data[i].hitbox1_x_pos = wd[6 + (9 * i)];
		walk_data[i].hitbox1_y_pos = wd[7 + (9 * i)];
		walk_data[i].hitbox1_height_s = wd[8 + (9 * i)];
		walk_data[i].hitbox1_width_s = wd[9 + (9 * i)];
	}

	fclose(fp1);

	//jumpデータ読み込み
	fopen_s(&fp1, "data\\JUMP_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &jd[i]) != EOF) {
		i++;
	}

	for (int i = 0; i < JUMPFlame; i++)
	{
		jump_data[i].hurtbox1_x_pos = jd[2 + (9 * i)];
		jump_data[i].hurtbox1_y_pos = jd[3 + (9 * i)];
		jump_data[i].hurtbox1_height_s = jd[4 + (9 * i)];
		jump_data[i].hurtbox1_width_s = jd[5 + (9 * i)];

		jump_data[i].hitbox1_x_pos = jd[6 + (9 * i)];
		jump_data[i].hitbox1_y_pos = jd[7 + (9 * i)];
		jump_data[i].hitbox1_height_s = jd[8 + (9 * i)];
		jump_data[i].hitbox1_width_s = jd[9 + (9 * i)];
	}

	fclose(fp1);

	//LightAttackデータ読み込み
	fopen_s(&fp1, "data\\LA_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &ld[i]) != EOF) {
		i++;
	}

	for (int i = 0; i <= LAFlame; i++)
	{
		la_data[i].hurtbox1_x_pos = ld[2 + (9 * i)];
		la_data[i].hurtbox1_y_pos = ld[3 + (9 * i)];
		la_data[i].hurtbox1_height_s = ld[4 + (9 * i)];
		la_data[i].hurtbox1_width_s = ld[5 + (9 * i)];

		la_data[i].hitbox1_x_pos = ld[6 + (9 * i)];
		la_data[i].hitbox1_y_pos = ld[7 + (9 * i)];
		la_data[i].hitbox1_height_s = ld[8 + (9 * i)];
		la_data[i].hitbox1_width_s = ld[9 + (9 * i)];
	}

	fclose(fp1);

	//MediumAttackデータ読み込み
	fopen_s(&fp1, "data\\MA_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &md[i]) != EOF) {
		i++;
	}

	for (int i = 0; i <= MAFlame; i++)
	{
		ma_data[i].hurtbox1_x_pos = md[2 + (9 * i)];
		ma_data[i].hurtbox1_y_pos = md[3 + (9 * i)];
		ma_data[i].hurtbox1_height_s = md[4 + (9 * i)];
		ma_data[i].hurtbox1_width_s = md[5 + (9 * i)];

		ma_data[i].hitbox1_x_pos = md[6 + (9 * i)];
		ma_data[i].hitbox1_y_pos = md[7 + (9 * i)];
		ma_data[i].hitbox1_height_s = md[8 + (9 * i)];
		ma_data[i].hitbox1_width_s = md[9 + (9 * i)];
	}

	fclose(fp1);

	//HeavyAttackデータ読み込み
	fopen_s(&fp1, "data\\HA_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &hd[i]) != EOF) {
		i++;
	}

	for (int i = 0; i <= HAFlame; i++)
	{
		ha_data[i].hurtbox1_x_pos = hd[2 + (9 * i)];
		ha_data[i].hurtbox1_y_pos = hd[3 + (9 * i)];
		ha_data[i].hurtbox1_height_s = hd[4 + (9 * i)];
		ha_data[i].hurtbox1_width_s = hd[5 + (9 * i)];

		ha_data[i].hitbox1_x_pos = hd[6 + (9 * i)];
		ha_data[i].hitbox1_y_pos = hd[7 + (9 * i)];
		ha_data[i].hitbox1_height_s = hd[8 + (9 * i)];
		ha_data[i].hitbox1_width_s = hd[9 + (9 * i)];
	}

	fclose(fp1);

	//Grap_readyデータ読み込み
	fopen_s(&fp1, "data\\Grap_ready_data.csv", "r");
	i = 1;

	while (fscanf_s(fp1, "%lf,", &grd[i]) != EOF) {
		i++;
	}

	for (int i = 0; i < GRAP_READY_Flame; i++)
	{
		grap_ready_data[i].hurtbox1_x_pos = grd[2 + (9 * i)];
		grap_ready_data[i].hurtbox1_y_pos = grd[3 + (9 * i)];
		grap_ready_data[i].hurtbox1_height_s = grd[4 + (9 * i)];
		grap_ready_data[i].hurtbox1_width_s = grd[5 + (9 * i)];

		grap_ready_data[i].hitbox1_x_pos = grd[6 + (9 * i)];
		grap_ready_data[i].hitbox1_y_pos = grd[7 + (9 * i)];
		grap_ready_data[i].hitbox1_height_s = grd[8 + (9 * i)];
		grap_ready_data[i].hitbox1_width_s = grd[9 + (9 * i)];
	}

	fclose(fp1);

}

void Player2::Update()
{
	Vector3 oldPosition = m_Position;

	Scene* scene = Manager::GetScene();

	//重力
	m_Velocity.y -= 0.015f;

	//抵抗
	m_Velocity.y -= m_Velocity.y * 0.01f;

	//移動
	m_Position += m_Velocity;

	//接地
	float groundHeight = 0.0f;

	float nowpos = this->m_Position.x;

	// 現在シーンを取得
	Player* playerobj = scene->GetGameObject<Player>();
	Vector3 playerpos = playerobj->GetPosition();

	// 位置が０以下なら地面位置にセットする
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

	//相手との位置関係によって向きを変える
	if (this->m_Position.y == groundHeight) {
		if (this->m_Position.x < playerpos.x)
		{
			muki = true;
			this->SetRotation(Vector3(0.0f, 1.5f, 0.0f));
		}
		else {
			muki = false;
			this->SetRotation(Vector3(0.0f, -1.5f, 0.0f));
		}
	}

	//////////////////////////////////////
	//入力
	//////////////////////////////////////
	if (Action == false && ste != Hit && ste != CriticalHit && ste != Guard && ste != Dying)
	{
		//ジャンプ
		if (Input::GetKeyTrigger(38))
		{
			m_Velocity.y = 0.25f;
			ste = Jump;
			old_ste = ste;

			m_Frame = 0;

			Action = true;
			Attackflg = true;
		}
		//弱攻撃
		if (Input::GetKeyTrigger('J'))
		{
			ste = Light_Attack;

			old_ste = ste;

			m_Frame = 0;

			Action = true;
			Attackflg = true;
		}
		//中攻撃
		else if (Input::GetKeyTrigger('K'))
		{
			ste = Medium_Attack;
			old_ste = ste;

			m_Frame = 0;

			Action = true;
			Attackflg = true;
		}
		//大攻撃
		else if (Input::GetKeyTrigger('L'))
		{
			ste = Heavy_Attack;
			old_ste = ste;

			m_Frame = 0;

			Action = true;
			Attackflg = true;
		}
		//投げ
		else if (Input::GetKeyTrigger('O'))
		{
			ste = Grap_ready;
			old_ste = ste;

			m_Frame = 0;

			this->grap_Frame = 0;
			this->Grap_hit = false;

			Action = true;
			Attackflg = true;
		}
	}

	//アクション中は動作しない
	if (Action == false && ste != Hit && ste != CriticalHit && ste != Guard && ste != Dying)
	{
		if (Input::GetKeyPress(39))
		{
			m_Position.x += 0.1f;
			ste = Walk;
			m_BlendRate += 0.1f;

			if (muki == false)
			{
				Block = true;
			}
		}
		if (Input::GetKeyPress(37))
		{
			m_Position.x -= 0.1f;
			ste = Walk;
			m_BlendRate += 0.1f;

			if (muki == true)
			{
				Block = true;
			}
		}
		//しゃがみ
		if (Input::GetKeyPress(40) && m_Position.y <= 0.01f)
		{
			m_Position.x = oldPosition.x;
			ste = Crouchi;
			m_BlendRate += 0.1f;
		}

	}
	
	//プレイヤーとプレイヤーの押し合い判定
	if (playerobj)
	{
		Vector3 position = playerobj->GetPosition();
		Vector3 scale = playerobj->GetScale() * 0.1f;

		AABB aabbPlayer;
		AABB aabbPlayer2;

		aabbPlayer2 = SetAABB(m_Position, fabs(2.5f), fabs(5.0f), 0.0f);
		aabbPlayer = SetAABB(position, fabs(2.5f), fabs(10.0f), 0.0f);

		bool sts = CollisionAABB(aabbPlayer2, aabbPlayer);

		if (sts)
		{
			m_Position.x = oldPosition.x;

			if (Input::GetKeyPress(39) && muki == true)
			{
				playerobj->Set_Push(true);
			}
			else if (Input::GetKeyPress(37) && muki == false)
			{
				playerobj->Set_Push(true);
			}
			else
			{
				playerobj->Set_Push(false);
			}
		}
		else
		{
			playerobj->Set_Push(false);
		}
	}

	if (this->Push_Flg == true)
	{
		if (muki == true)
		{
			m_Position.x -= 0.1f;
		}
		if (muki == false)
		{
			m_Position.x += 0.1f;
		}
	}
	
	if (ste != Hit && ste != CriticalHit && ste != Guard && ste != Dying)
	{
		if (Action)
		{
			ste = old_ste;

			LightAttack_data ldata;
			MediumAttack_data mdata;
			HeavyAttack_data hdata;

			if (ste == Jump)
			{
				m_BlendRate += 0.1f;

				//edataにjump_dataを格納
				edata[m_Frame].hurtbox1_x_pos = jump_data[m_Frame].hurtbox1_x_pos;
				edata[m_Frame].hurtbox1_y_pos = jump_data[m_Frame].hurtbox1_y_pos;
				edata[m_Frame].hurtbox1_height_s = jump_data[m_Frame].hurtbox1_height_s;
				edata[m_Frame].hurtbox1_width_s = jump_data[m_Frame].hurtbox1_width_s;

				edata[m_Frame].hitbox1_x_pos = jump_data[m_Frame].hitbox1_x_pos;
				edata[m_Frame].hitbox1_y_pos = jump_data[m_Frame].hitbox1_y_pos;
				edata[m_Frame].hitbox1_height_s = jump_data[m_Frame].hitbox1_height_s;
				edata[m_Frame].hitbox1_width_s = jump_data[m_Frame].hitbox1_width_s;

				if (m_Frame > jumpflame)
				{
					Action = false;
				}
			}

			if (ste == Light_Attack)
			{
				m_BlendRate += 0.1f;
				
				//edataにla_dataを格納
				edata[m_Frame].hurtbox1_x_pos = la_data[m_Frame].hurtbox1_x_pos;
				edata[m_Frame].hurtbox1_y_pos = la_data[m_Frame].hurtbox1_y_pos;
				edata[m_Frame].hurtbox1_height_s = la_data[m_Frame].hurtbox1_height_s;
				edata[m_Frame].hurtbox1_width_s = la_data[m_Frame].hurtbox1_width_s;

				edata[m_Frame].hitbox1_x_pos = la_data[m_Frame].hitbox1_x_pos;
				edata[m_Frame].hitbox1_y_pos = la_data[m_Frame].hitbox1_y_pos;
				edata[m_Frame].hitbox1_height_s = la_data[m_Frame].hitbox1_height_s;
				edata[m_Frame].hitbox1_width_s = la_data[m_Frame].hitbox1_width_s;

				if (m_Frame > latkflame[0])
				{
					Action = false;
				}
			}

			if (ste == Medium_Attack)
			{
				m_BlendRate += 0.1f;

				//edataにma_dataを格納
				edata[m_Frame].hurtbox1_x_pos = ma_data[m_Frame].hurtbox1_x_pos;
				edata[m_Frame].hurtbox1_y_pos = ma_data[m_Frame].hurtbox1_y_pos;
				edata[m_Frame].hurtbox1_height_s = ma_data[m_Frame].hurtbox1_height_s;
				edata[m_Frame].hurtbox1_width_s = ma_data[m_Frame].hurtbox1_width_s;

				edata[m_Frame].hitbox1_x_pos = ma_data[m_Frame].hitbox1_x_pos;
				edata[m_Frame].hitbox1_y_pos = ma_data[m_Frame].hitbox1_y_pos;
				edata[m_Frame].hitbox1_height_s = ma_data[m_Frame].hitbox1_height_s;
				edata[m_Frame].hitbox1_width_s = ma_data[m_Frame].hitbox1_width_s;

				if (m_Frame > matkflame[0])
				{
					Action = false;
				}
			}

			if (ste == Heavy_Attack)
			{
				m_BlendRate += 0.1f;

				//edataにha_dataを格納
				edata[m_Frame].hurtbox1_x_pos = ha_data[m_Frame].hurtbox1_x_pos;
				edata[m_Frame].hurtbox1_y_pos = ha_data[m_Frame].hurtbox1_y_pos;
				edata[m_Frame].hurtbox1_height_s = ha_data[m_Frame].hurtbox1_height_s;
				edata[m_Frame].hurtbox1_width_s = ha_data[m_Frame].hurtbox1_width_s;

				edata[m_Frame].hitbox1_x_pos = ha_data[m_Frame].hitbox1_x_pos;
				edata[m_Frame].hitbox1_y_pos = ha_data[m_Frame].hitbox1_y_pos;
				edata[m_Frame].hitbox1_height_s = ha_data[m_Frame].hitbox1_height_s;
				edata[m_Frame].hitbox1_width_s = ha_data[m_Frame].hitbox1_width_s;

				if (m_Frame > hatkflame[0])
				{
					Action = false;
				}
			}

			if (ste == Grap_ready)
			{
				//edataにgrap_dataを格納
				edata[m_Frame].hurtbox1_x_pos = grap_ready_data[m_Frame].hurtbox1_x_pos;
				edata[m_Frame].hurtbox1_y_pos = grap_ready_data[m_Frame].hurtbox1_y_pos;
				edata[m_Frame].hurtbox1_height_s = grap_ready_data[m_Frame].hurtbox1_height_s;
				edata[m_Frame].hurtbox1_width_s = grap_ready_data[m_Frame].hurtbox1_width_s;

				edata[m_Frame].hitbox1_x_pos = grap_ready_data[m_Frame].hitbox1_x_pos;
				edata[m_Frame].hitbox1_y_pos = grap_ready_data[m_Frame].hitbox1_y_pos;
				edata[m_Frame].hitbox1_height_s = grap_ready_data[m_Frame].hitbox1_height_s;
				edata[m_Frame].hitbox1_width_s = grap_ready_data[m_Frame].hitbox1_width_s;

				m_BlendRate += 0.1f;

				if (m_Frame > 30)
				{
					Action = false;
					//ste = Grap_motion;
				}
			}
		}
		else if (ste == Walk)
		{
			if (Input::GetKeyPress(39) || Input::GetKeyPress(37))
			{
				ste = Walk;
			}
			else
			{
				ste = Idle;
				Block = false;
			}
		}
		else if (ste == Crouchi)
		{
			if (Input::GetKeyPress(40))
			{
				ste = Crouchi;
			}
			else
			{
				ste = Idle;
				Block = false;
			}
		}
		else
		{
			//m_BlendRate -= 0.1f;
			ste = Idle;
			Block = false;
		}
	}

	if (ste == Idle)
	{
		m_BlendRate -= 0.1f;

		//edataにidle_dataを格納
		edata[m_Frame].hurtbox1_x_pos = idle_data[m_Frame].hurtbox1_x_pos;
		edata[m_Frame].hurtbox1_y_pos = idle_data[m_Frame].hurtbox1_y_pos;
		edata[m_Frame].hurtbox1_height_s = idle_data[m_Frame].hurtbox1_height_s;
		edata[m_Frame].hurtbox1_width_s = idle_data[m_Frame].hurtbox1_width_s;

		edata[m_Frame].hitbox1_x_pos = idle_data[m_Frame].hitbox1_x_pos;
		edata[m_Frame].hitbox1_y_pos = idle_data[m_Frame].hitbox1_y_pos;
		edata[m_Frame].hitbox1_height_s = idle_data[m_Frame].hitbox1_height_s;
		edata[m_Frame].hitbox1_width_s = idle_data[m_Frame].hitbox1_width_s;
	}

	if (ste == Crouchi)
	{
		//edataにcrouchi_dataを格納
		edata[m_Frame].hurtbox1_x_pos = crouchi_data[m_Frame].hurtbox1_x_pos;
		edata[m_Frame].hurtbox1_y_pos = crouchi_data[m_Frame].hurtbox1_y_pos;
		edata[m_Frame].hurtbox1_height_s = crouchi_data[m_Frame].hurtbox1_height_s;
		edata[m_Frame].hurtbox1_width_s = crouchi_data[m_Frame].hurtbox1_width_s;

		edata[m_Frame].hitbox1_x_pos = crouchi_data[m_Frame].hitbox1_x_pos;
		edata[m_Frame].hitbox1_y_pos = crouchi_data[m_Frame].hitbox1_y_pos;
		edata[m_Frame].hitbox1_height_s = crouchi_data[m_Frame].hitbox1_height_s;
		edata[m_Frame].hitbox1_width_s = crouchi_data[m_Frame].hitbox1_width_s;
	}

	if (ste == Walk || ste == Hit || ste == Guard)
	{
		//edataにwalk_dataを格納
		edata[m_Frame].hurtbox1_x_pos = walk_data[m_Frame].hurtbox1_x_pos;
		edata[m_Frame].hurtbox1_y_pos = walk_data[m_Frame].hurtbox1_y_pos;
		edata[m_Frame].hurtbox1_height_s = walk_data[m_Frame].hurtbox1_height_s;
		edata[m_Frame].hurtbox1_width_s = walk_data[m_Frame].hurtbox1_width_s;

		edata[m_Frame].hitbox1_x_pos = walk_data[m_Frame].hitbox1_x_pos;
		edata[m_Frame].hitbox1_y_pos = walk_data[m_Frame].hitbox1_y_pos;
		edata[m_Frame].hitbox1_height_s = walk_data[m_Frame].hitbox1_height_s;
		edata[m_Frame].hitbox1_width_s = walk_data[m_Frame].hitbox1_width_s;
	}

	if (ste == CriticalHit)
	{
		if (muki == false)edata[m_Frame].hurtbox1_x_pos = walk_data[m_Frame].hurtbox1_x_pos + 4.0f;
		if (muki == true)edata[m_Frame].hurtbox1_x_pos = walk_data[m_Frame].hurtbox1_x_pos - 4.0f;
		edata[m_Frame].hurtbox1_y_pos = walk_data[m_Frame].hurtbox1_y_pos;
		edata[m_Frame].hurtbox1_height_s = walk_data[m_Frame].hurtbox1_height_s;
		edata[m_Frame].hurtbox1_width_s = walk_data[m_Frame].hurtbox1_width_s;

		edata[m_Frame].hitbox1_x_pos = walk_data[m_Frame].hitbox1_x_pos;
		edata[m_Frame].hitbox1_y_pos = walk_data[m_Frame].hitbox1_y_pos;
		edata[m_Frame].hitbox1_height_s = walk_data[m_Frame].hitbox1_height_s;
		edata[m_Frame].hitbox1_width_s = walk_data[m_Frame].hitbox1_width_s;
	}

	if(GetNowHp() <= 0)
	{ 
		ste = Dying;
		m_BlendRate += 0.1f;

		if (old_ste != Dying)
		{
			m_Frame = 0;
		}
	}
	
	//当たり判定
	{
		P2hurtbox* hurtobj = scene->GetGameObject<P2hurtbox>();
		P2hitbox* hitobj = scene->GetGameObject<P2hitbox>();

		edata[m_Frame].hurtbox1_height_s = fabs(edata[m_Frame].hurtbox1_height_s);
		edata[m_Frame].hurtbox1_width_s = fabs(edata[m_Frame].hurtbox1_width_s);

		hurtobj->Set_xpos(edata[m_Frame].hurtbox1_x_pos);
		hurtobj->Set_ypos(edata[m_Frame].hurtbox1_y_pos);

		hurtobj->Set_eheight(abs(edata[m_Frame].hurtbox1_height_s));
		hurtobj->Set_ewidth(abs(edata[m_Frame].hurtbox1_width_s));

		edata[m_Frame].hitbox1_height_s = fabs(edata[m_Frame].hitbox1_height_s);
		edata[m_Frame].hitbox1_width_s = fabs(edata[m_Frame].hitbox1_width_s);

		hitobj->Set_xpos(edata[m_Frame].hitbox1_x_pos);
		hitobj->Set_ypos(edata[m_Frame].hitbox1_y_pos);

		hitobj->Set_eheight(abs(edata[m_Frame].hitbox1_height_s));
		hitobj->Set_ewidth(abs(edata[m_Frame].hitbox1_width_s));


		LightAttack_data ldata;
		MediumAttack_data mdata;
		HeavyAttack_data hdata;

		Vector3 hurtposition = hurtobj->GetPosition();
		Vector3 hurtscale = hurtobj->GetScale();
		Vector3 hitposition = hitobj->GetPosition();
		Vector3 hitscale = hitobj->GetScale();

		//当たり判定をセット
		this->player_Hurtbox = SetAABB3(hurtposition, fabs(hurtscale.x), fabs(hurtscale.y), 0.0f);

		if (hitscale.x != 0.0f && hitscale.y != 0.0f)
		{
			this->player_Attackbox = SetAABB3(hitposition, fabs(hitscale.x), fabs(hitscale.y), 0.0f);
		}
		else
		{
			this->player_Attackbox = SetAABB3(Vector3(0.0f, 5000.0f, 0.0f), fabs(hitscale.x), fabs(hitscale.y), 0.0f);
		}

		AABB player2_Attackbox;

		player2_Attackbox = playerobj->Get_Attackbox();	//P2のやられ判定取得

		bool sts = CollisionAABB(this->player_Hurtbox, player2_Attackbox);

		if (sts && playerobj->Get_Attackflg() == true && playerobj->Get_Combo_count() < COMBO_MAX && ste != Dying && ste != Win && this->Grap_hit != true)
		{	
			if (playerobj->Get_status() == Grap_ready && this->ste != Grap_ready)//投げ
			{
				this->Set_Grap_hit(true);
				m_Frame = 0;
			}
			else if (this->Get_Block() == false)	//ガードしているか
			{
				if (playerobj->Get_status() == Light_Attack)		//当たった技がLight_Attackなら
				{ 
					playerobj->Combo_add();
					this->DecNowHp(ldata.dmg); 
					this->Set_Hitflame(ldata.hit_Frame);
					ste = Hit;
					m_Frame = 0;
					if (playerobj->Get_Combo_count() == COMBO_MAX)		//コンボ上限に達していないか
					{
						this->DecNowHp(ldata.dmg);
					}
				}
				if (playerobj->Get_status() == Medium_Attack)		//当たった技がMedium_Attackなら
				{
					playerobj->Combo_add();
					this->DecNowHp(mdata.dmg); 
					this->Set_Hitflame(mdata.hit_Frame);
					ste = Hit;
					m_Frame = 0;
					if (playerobj->Get_Combo_count() == COMBO_MAX)		//コンボ上限に達していないか
					{
						this->DecNowHp(mdata.dmg);
					}
				}
				if (playerobj->Get_status() == Heavy_Attack)		//当たった技がHeavy_Attackなら
				{
					playerobj->Combo_add();
					this->DecNowHp(hdata.dmg);
					this->Set_Hitflame(hdata.hit_Frame);
					ste = Hit;
					m_Frame = 0;
					if (playerobj->Get_Combo_count() == COMBO_MAX)		//コンボ上限に達していないか
					{
						this->DecNowHp(hdata.dmg);
					}
				}

				if (playerobj->Get_Combo_count() == COMBO_MAX)		//コンボ上限に達していないか
				{
					ste = CriticalHit;
				}
			}
			else
			{				
				//ガードした時の処理
				if (playerobj->Get_status() == Light_Attack)
				{
					this->Set_Guardflame(ldata.guard_Frame);
				}
				if (playerobj->Get_status() == Medium_Attack)
				{
					this->Set_Guardflame(mdata.guard_Frame);
				}
				if (playerobj->Get_status() == Heavy_Attack)
				{
					this->Set_Guardflame(hdata.guard_Frame);
				}

				ste = Guard;
				m_Frame = 0;
			}

			playerobj->Set_Attackflg(false);
		}
	}

	if (ste == Hit)
	{	
		m_BlendRate += 0.1f;

		if (old_ste != Hit)
		{
			m_Frame = 0;
		}

		if (m_Frame > hitflame)
		{
			ste = Idle;
			Action = false;
			playerobj->Set_Combo(0);
		}
	}

	if (ste == CriticalHit)
	{
		m_BlendRate += 0.1f;
		this->grap_Frame = 0;

		if (m_Frame > CriticalFlame)
		{
			ste = Idle;
			Action = false;
			playerobj->Set_Combo(0);

			//ダウンさせられた時のノックバック　向きによって変わる
			Vector3 nowposition = this->GetPosition();
			if (muki == false)this->SetPosition(Vector3(nowposition.x + 1.0f, nowposition.y, nowposition.z));
			if (muki == true)this->SetPosition(Vector3(nowposition.x - 1.0f, nowposition.y, nowposition.z));
		}
	}

	//投げ
	if (this->Grap_hit == true)
	{
		Grap_data gdata;
		this->grap_Frame++;

		if (this->grap_Frame >= GRAP_GRACE_Flame)
		{
			ste = CriticalHit;
			this->DecNowHp(gdata.dmg);
			this->Set_Grap_hit(false);
		}
	}

	if (playerobj->grap_Frame >= GRAP_GRACE_Flame && ste != Win)
	{
		ste = Grap_motion;
	}

	if (ste == Grap_motion)
	{
		if (old_ste != Grap_motion)
		{
			m_Frame = 15;
		}
		m_BlendRate += 0.1f;

		if (m_Frame > 30)
		{
			Action = false;
			ste = Idle;
		}
	}

	if (ste == Guard)
	{
		m_BlendRate += 0.1f;
		if (old_ste != Guard)
		{
			m_Frame = 0;
		}

		if (m_Frame > guardflame)
		{
			ste = Idle;
			Action = false;
		}
	}

	if (playerobj->GetNowHp() <= 0)
	{
		ste = Win;

		if (old_ste != Win)
		{
			m_Frame = 0;

			Action = true;
		}
	}

	m_Frame++;

	if (m_Frame > 101 && ste != Dying)m_Frame = 0;

	if (m_Position.x > movelimit) {
		m_Position.x = movelimit;
	}
	if (m_Position.x < -movelimit) {
		m_Position.x = -movelimit;
	}

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;

	old_ste = ste;

	//相手との距離が一定以上なら移動できない
	float playerdis = (playerpos.x - this->m_Position.x) / 2.0f;

	if (fabsf(playerdis) > 6.0f)
	{
		this->m_Position.x = nowpos;
	}
}

void Player2::PreDraw()
{
	switch (ste)
	{
	case Player2::Idle:
		m_Model->Update("Idle", m_Frame, "Idle", m_Frame, m_BlendRate);
		break;
	case Player2::Walk:
		m_Model->Update("Idle", m_Frame, "Walk", m_Frame, m_BlendRate);
		break;
	case Player2::Jump:
		m_Model->Update("Idle", m_Frame, "Jump", m_Frame, m_BlendRate);
		break;
	case Player2::Crouchi:
		m_Model->Update("Idle", m_Frame, "Crouchi", m_Frame, m_BlendRate);
		break;
	case Player2::Light_Attack:
		m_Model->Update("Idle", m_Frame, "Light_Attack", m_Frame, m_BlendRate);
		break;
	case Player2::Medium_Attack:
		m_Model->Update("Idle", m_Frame, "Medium_Attack", m_Frame, m_BlendRate);
		break;
	case Player2::Heavy_Attack:
		m_Model->Update("Idle", m_Frame, "Heavy_Attack", m_Frame, m_BlendRate);
		break;
	case Player2::Jump_Attack:
		m_Model->Update("Idle", m_Frame, "Jump_Attack", m_Frame, m_BlendRate);
		break;
	case Player2::SP_Attack:
		m_Model->Update("Idle", m_Frame, "SP_Attack", m_Frame, m_BlendRate);
		break;
	case Player2::Hit:
		m_Model->Update("Idle", m_Frame, "Hit", m_Frame, m_BlendRate);
		break;
	case Player2::CriticalHit:
		m_Model->Update("Idle", m_Frame, "CriticalHit", m_Frame, m_BlendRate);
		break;
	case Player2::Dying:
		m_Model->Update("Idle", m_Frame, "Dying", m_Frame, m_BlendRate);
		break;
	case Player2::Win:
		m_Model->Update("Idle", m_Frame, "Win", m_Frame, m_BlendRate);
		break;
	case Player2::Guard:
		m_Model->Update("Idle", m_Frame, "Guard", m_Frame, m_BlendRate);
		break;
	case Player2::Grap_ready:
		m_Model->Update("Idle", m_Frame, "Grap_ready", m_Frame, m_BlendRate);
		break;
	case Player2::Grap_motion:
		m_Model->Update("Idle", m_Frame, "Grap_motion", m_Frame, m_BlendRate);
		break;
	default:
		break;
	}
}

void Player2::Set_Guardflame(int gf)
{
	guardflame = gf;
}

void Player2::Set_Hitflame(int hf)
{
	hitflame = hf;
}
