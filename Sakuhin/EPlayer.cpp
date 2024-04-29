#include "EPlayer.h"
#include "shader.h"
#include "shadow.h"
#include "ehurtbox.h"
#include "ehitbox1.h"
#include "scene.h"
#include "manager.h"
#include <stdio.h>
#include "title.h"

#include "ehitbox2.h"
#include "ehurtbox2.h"

#define HURT_XPOS_SLIDER_MAX 5.0f
#define HURT_YPOS_SLIDER_MAX 3.0f
#define HURT_HEIGHT_SLIDER_MAX 5.0f
#define HURT_WIDTH_SLIDER_MAX 5.0f

#define HIT_XPOS_SLIDER_MAX 5.0f
#define HIT_YPOS_SLIDER_MAX 3.0f
#define HIT_HEIGHT_SLIDER_MAX 5.0f
#define HIT_WIDTH_SLIDER_MAX 5.0f

#define _CRT_SECURE_NO_WARNINGS

void EPlayer::Set_move(bool bo)
{
	move = bo;
}

void EPlayer::Set_m_Flame(int mfl)
{
	this->m_Frame = mfl;
}

int EPlayer::Get_m_Flame()
{
	return m_Frame;
}


void EPlayer::ShowDebugWindow()
{
    static float slider1 = 1000.0;
    static int flame1 = 0;
    static int allflame = 0;
    
    static int mode = 0;
    static bool isEnable = true;
    
    //プレイヤーの状態
    enum player_ste
    {
        IDLE,
        WALK,
        JUMP,
        CROUCHI,
        LIGHT_ATTACK,
        MEDIUM_ATTACK,
        HEAVY_ATTACK,
        Jump_Attack,
        SP_Attack,
        Hit,
        Dying,
        Win,
        Guard,
        Grap_ready,
        Grap_motion
    };
    
    // 現在シーンを取得
    Scene* scene = Manager::GetScene();
    Ehurtbox* hurtobj = scene->GetGameObject<Ehurtbox>();
    Ehitbox1* hitobj = scene->GetGameObject<Ehitbox1>();
    
    flame1 = this->Get_m_Flame();
    
    if (this)
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(500, 600));
        ImGui::Begin("Edit Window");
        ImGui::Text("STATUS");
        ImGui::RadioButton("Idle", &mode, IDLE); ImGui::SameLine(); ImGui::RadioButton("Walk", &mode, WALK); ImGui::RadioButton("Jump", &mode, JUMP); ImGui::RadioButton("Crouchi", &mode, CROUCHI);
        ImGui::RadioButton("Light_Attack", &mode, LIGHT_ATTACK); ImGui::SameLine(); ImGui::RadioButton("Medium_ATTACK", &mode, MEDIUM_ATTACK); ImGui::RadioButton("Heavy_ATTACK", &mode, HEAVY_ATTACK);
        ImGui::RadioButton("Grap_ready", &mode, Grap_ready); ImGui::SameLine();

        ImGui::Text("Move");
        ImGui::Checkbox("Move", &isEnable);
    
        if (isEnable)
        {
            this->Set_move(true);
        }
        else
        {
            this->Set_move(false); //動きを停止 
    
            //フレームをいじれるように
            ImGui::Text("Flame");
            ImGui::SliderInt("Flame", &flame1, 0, allflame);
            this->Set_m_Flame(flame1);
        }
    
        //Idleが押されていたら
        if (mode == IDLE)
        {
            this->Set_status(PlayerBase::player_ste::Idle);
    
            allflame = 100;

            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &idle_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &idle_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &idle_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &idle_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &idle_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &idle_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &idle_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &idle_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\IDLE_data.csv", "w");

                for (int i = 0; i < IDLEFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, idle_data[i].hurtbox1_x_pos, idle_data[i].hurtbox1_y_pos, idle_data[i].hurtbox1_height_s, idle_data[i].hurtbox1_width_s, idle_data[i].hitbox1_x_pos, idle_data[i].hitbox1_y_pos, idle_data[i].hitbox1_height_s, idle_data[i].hitbox1_width_s);
                }
                fclose(fp1);
            }

            edata[flame1].hurtbox1_x_pos = idle_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = idle_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = idle_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = idle_data[flame1].hurtbox1_width_s;

            edata[flame1].hitbox1_x_pos = idle_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = idle_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = idle_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = idle_data[flame1].hitbox1_width_s;


        }

        //Walkが押されていたら
        if (mode == WALK)
        {
            this->Set_status(PlayerBase::player_ste::Walk);
    
            allflame = 100;

            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &walk_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &walk_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &walk_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &walk_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &walk_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &walk_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &walk_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &walk_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\WALK_data.csv", "w");

                for (int i = 0; i < WALKFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, walk_data[i].hurtbox1_x_pos, walk_data[i].hurtbox1_y_pos, walk_data[i].hurtbox1_height_s, walk_data[i].hurtbox1_width_s, walk_data[i].hitbox1_x_pos, walk_data[i].hitbox1_y_pos, walk_data[i].hitbox1_height_s, walk_data[i].hitbox1_width_s);
                }
                fclose(fp1);
            }

            edata[flame1].hurtbox1_x_pos = walk_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = walk_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = walk_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = walk_data[flame1].hurtbox1_width_s;

            edata[flame1].hitbox1_x_pos = walk_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = walk_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = walk_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = walk_data[flame1].hitbox1_width_s;

        }

        //Jumoが押されていたら
        if (mode == JUMP)
        {
            this->Set_status(PlayerBase::player_ste::Jump);
    
            allflame = 40;

            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &jump_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &jump_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &jump_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &jump_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &jump_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &jump_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &jump_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &jump_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\JUMP_data.csv", "w");

                for (int i = 0; i < JUMPFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, jump_data[i].hurtbox1_x_pos, jump_data[i].hurtbox1_y_pos, jump_data[i].hurtbox1_height_s, jump_data[i].hurtbox1_width_s, jump_data[i].hitbox1_x_pos, jump_data[i].hitbox1_y_pos, jump_data[i].hitbox1_height_s, jump_data[i].hitbox1_width_s);
                }
                fclose(fp1);
            }


            edata[flame1].hurtbox1_x_pos = jump_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = jump_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = jump_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = jump_data[flame1].hurtbox1_width_s;

            edata[flame1].hitbox1_x_pos = jump_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = jump_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = jump_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = jump_data[flame1].hitbox1_width_s;
        }

        //Crouchiが押されていたら
        if (mode == Crouchi)
        {
            this->Set_status(PlayerBase::player_ste::Crouchi);

            allflame = 100;

            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &crouchi_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &crouchi_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &crouchi_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &crouchi_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &crouchi_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &crouchi_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &crouchi_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &crouchi_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\CROUCHI_data.csv", "w");

                for (int i = 0; i < CROUCHIFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, crouchi_data[i].hurtbox1_x_pos, crouchi_data[i].hurtbox1_y_pos, crouchi_data[i].hurtbox1_height_s, crouchi_data[i].hurtbox1_width_s, crouchi_data[i].hitbox1_x_pos, crouchi_data[i].hitbox1_y_pos, crouchi_data[i].hitbox1_height_s, crouchi_data[i].hitbox1_width_s);
                }
                fclose(fp1);
            }


            edata[flame1].hurtbox1_x_pos = crouchi_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = crouchi_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = crouchi_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = crouchi_data[flame1].hurtbox1_width_s;

            edata[flame1].hitbox1_x_pos = crouchi_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = crouchi_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = crouchi_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = crouchi_data[flame1].hitbox1_width_s;
        }

        //LIGHT_ATTACKが押されていたら
        if (mode == LIGHT_ATTACK)
        {
            this->Set_status(PlayerBase::player_ste::Light_Attack);
    
            allflame = 15;
    
            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &la_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &la_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &la_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &la_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);
    
                ImGui::TreePop();
            }
    
            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &la_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &la_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &la_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &la_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);
            
                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\LA_data.csv", "w");

                for (int i = 0; i < LAFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, la_data[i].hurtbox1_x_pos, la_data[i].hurtbox1_y_pos, la_data[i].hurtbox1_height_s, la_data[i].hurtbox1_width_s, la_data[i].hitbox1_x_pos, la_data[i].hitbox1_y_pos, la_data[i].hitbox1_height_s, la_data[i].hitbox1_width_s);
                }
                fclose(fp1);
            }
            
    
            edata[flame1].hurtbox1_x_pos = la_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = la_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = la_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = la_data[flame1].hurtbox1_width_s;
    
            edata[flame1].hitbox1_x_pos = la_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = la_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = la_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = la_data[flame1].hitbox1_width_s;
        }

        //MEDIUM_ATTACKが押されていたら
        if (mode == MEDIUM_ATTACK)
        {
            this->Set_status(PlayerBase::player_ste::Medium_Attack);
    
            allflame = 25;
    
            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &ma_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &ma_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &ma_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &ma_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);
    
                ImGui::TreePop();
            }
    
            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &ma_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &ma_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &ma_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &ma_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);
            
                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\MA_data.csv", "w");

                for (int i = 0; i < MAFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, ma_data[i].hurtbox1_x_pos, ma_data[i].hurtbox1_y_pos, ma_data[i].hurtbox1_height_s, ma_data[i].hurtbox1_width_s, ma_data[i].hitbox1_x_pos, ma_data[i].hitbox1_y_pos, ma_data[i].hitbox1_height_s, ma_data[i].hitbox1_width_s);
                }
                fclose(fp1);

            }
    
            edata[flame1].hurtbox1_x_pos = ma_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = ma_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = ma_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = ma_data[flame1].hurtbox1_width_s;
    
            edata[flame1].hitbox1_x_pos = ma_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = ma_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = ma_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = ma_data[flame1].hitbox1_width_s;
        }

        //HEAVY_ATTACKが押されていたら
        if (mode == HEAVY_ATTACK)
        {
            this->Set_status(PlayerBase::player_ste::Heavy_Attack);
    
            allflame = 35;
    
            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &ha_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &ha_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &ha_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &ha_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);
    
                ImGui::TreePop();
            }
    
            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &ha_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &ha_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);
    
                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &ha_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &ha_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);
            
                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\HA_data.csv", "w");

                for (int i = 0; i < HAFlame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, ha_data[i].hurtbox1_x_pos, ha_data[i].hurtbox1_y_pos, ha_data[i].hurtbox1_height_s, ha_data[i].hurtbox1_width_s, ha_data[i].hitbox1_x_pos, ha_data[i].hitbox1_y_pos, ha_data[i].hitbox1_height_s, ha_data[i].hitbox1_width_s);
                }
                fclose(fp1);

            }
    
            edata[flame1].hurtbox1_x_pos = ha_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = ha_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = ha_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = ha_data[flame1].hurtbox1_width_s;
    
            edata[flame1].hitbox1_x_pos = ha_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = ha_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = ha_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = ha_data[flame1].hitbox1_width_s;
        }

        //Grap_readyが押されていたら
        if (mode == Grap_ready)
        {
            this->Set_status(PlayerBase::player_ste::Grap_ready);

            allflame = 30;

            if (ImGui::TreeNode("Hurt Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &grap_ready_data[flame1].hurtbox1_x_pos, -HURT_XPOS_SLIDER_MAX, HURT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &grap_ready_data[flame1].hurtbox1_y_pos, -HURT_YPOS_SLIDER_MAX, HURT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &grap_ready_data[flame1].hurtbox1_height_s, 0.0f, HURT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &grap_ready_data[flame1].hurtbox1_width_s, 0.0f, HURT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Hit Box 1"))
            {
                ImGui::Text("Pos");
                ImGui::SliderFloat("X_Pos", &grap_ready_data[flame1].hitbox1_x_pos, -HIT_XPOS_SLIDER_MAX, HIT_XPOS_SLIDER_MAX);
                ImGui::SliderFloat("Y_Pos", &grap_ready_data[flame1].hitbox1_y_pos, -HIT_YPOS_SLIDER_MAX, HIT_YPOS_SLIDER_MAX);

                ImGui::Text("height & width");
                ImGui::SliderFloat("height", &grap_ready_data[flame1].hitbox1_height_s, 0.0f, HIT_HEIGHT_SLIDER_MAX);
                ImGui::SliderFloat("width", &grap_ready_data[flame1].hitbox1_width_s, 0.0f, HIT_WIDTH_SLIDER_MAX);

                ImGui::TreePop();
            }

            if (ImGui::Button("save"))
            {
                FILE* fp1;

                fopen_s(&fp1, "data\\Grap_ready_data.csv", "w");

                for (int i = 0; i < GRAP_READY_Flame; i++)
                {
                    fprintf(fp1, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, grap_ready_data[i].hurtbox1_x_pos, grap_ready_data[i].hurtbox1_y_pos, grap_ready_data[i].hurtbox1_height_s, grap_ready_data[i].hurtbox1_width_s, grap_ready_data[i].hitbox1_x_pos, grap_ready_data[i].hitbox1_y_pos, grap_ready_data[i].hitbox1_height_s, grap_ready_data[i].hitbox1_width_s);
                }
                fclose(fp1);

            }

            edata[flame1].hurtbox1_x_pos = grap_ready_data[flame1].hurtbox1_x_pos;
            edata[flame1].hurtbox1_y_pos = grap_ready_data[flame1].hurtbox1_y_pos;
            edata[flame1].hurtbox1_height_s = grap_ready_data[flame1].hurtbox1_height_s;
            edata[flame1].hurtbox1_width_s = grap_ready_data[flame1].hurtbox1_width_s;

            edata[flame1].hitbox1_x_pos = grap_ready_data[flame1].hitbox1_x_pos;
            edata[flame1].hitbox1_y_pos = grap_ready_data[flame1].hitbox1_y_pos;
            edata[flame1].hitbox1_height_s = grap_ready_data[flame1].hitbox1_height_s;
            edata[flame1].hitbox1_width_s = grap_ready_data[flame1].hitbox1_width_s;
        }
    
        if (flame1 > allflame)
        {
            flame1 = 0;
        }
    
        edata[flame1].hurtbox1_height_s = fabs(edata[flame1].hurtbox1_height_s);
        edata[flame1].hurtbox1_width_s = fabs(edata[flame1].hurtbox1_width_s);

        Ehitbox2* hitobj2 = scene->GetGameObject<Ehitbox2>();
        Ehurtbox2* hurtobj2 = scene->GetGameObject<Ehurtbox2>();

        hurtobj2->Set_xpos(edata[flame1].hurtbox1_x_pos);
        hurtobj2->Set_ypos(edata[flame1].hurtbox1_y_pos);

        hurtobj2->Set_eheight(abs(edata[flame1].hurtbox1_height_s));
        hurtobj2->Set_ewidth(abs(edata[flame1].hurtbox1_width_s));

        hitobj2->Set_xpos(edata[flame1].hitbox1_x_pos);
        hitobj2->Set_ypos(edata[flame1].hitbox1_y_pos);

        hitobj2->Set_eheight(abs(edata[flame1].hitbox1_height_s));
        hitobj2->Set_ewidth(abs(edata[flame1].hitbox1_width_s));

       
        if (ImGui::Button("return TITLE"))
        {
            Manager::SetScene<Title>();

        }

        ImGui::End();
    
    }
}

void EPlayer::Init()
{
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
	m_Model->LoadAnimation("asset\\model\\Dying.fbx", "Dying");
	m_Model->LoadAnimation("asset\\model\\win.fbx", "Win");
	m_Model->LoadAnimation("asset\\model\\Block2.fbx", "Guard");
    m_Model->LoadAnimation("asset\\model\\Grap_ready.fbx", "Grap_ready");
    m_Model->LoadAnimation("asset\\model\\Grap_motion.fbx", "Grap_motion");

	AddComponent<Shadow>()->SetSize(1.5f);

	m_Scale = DirectX::SimpleMath::Vector3::Vector3(0.03f, 0.03f, 0.03f);

    //ファイルからのデータを格納する
    double ld[MaxN] = { 0.0 };
    double md[MaxN] = { 0.0 };
    double hd[MaxN] = { 0.0 };
    double id[MaxN] = { 0.0 };
    double wd[MaxN] = { 0.0 };
    double jd[MaxN] = { 0.0 };
    double cd[MaxN] = { 0.0 };
    double grd[MaxN] = { 0.0 };

    int i;
    FILE* fp1;

    //IDLEデータ読み込み
    fopen_s(&fp1, "data\\IDLE_data.csv", "r");
    i = 1;

    while (fscanf_s(fp1, "%lf,", &id[i]) != EOF) {
        i++;
    }

    for (int i = 0; i <= IDLEFlame; i++)
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

    //WALKデータ読み込み
    fopen_s(&fp1, "data\\WALK_data.csv", "r");
    i = 1;

    while (fscanf_s(fp1, "%lf,", &wd[i]) != EOF) {
        i++;
    }

    for (int i = 0; i <= WALKFlame; i++)
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

    //JUMPデータ読み込み
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

    //JUMPデータ読み込み
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

        la_data[i].hitbox1_x_pos = ld[6+ (9 * i)];
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

void EPlayer::Update()
{
	if (old_ste != ste)
	{
		m_Frame = 0;
		m_BlendRate = 0;
	}

	if (ste == Idle)
	{
		m_BlendRate -= 0.1f;

        if (m_Frame >= IDLEFlame)
        {
            m_Frame = 0;
        }
	}
	if (ste == Walk)
	{
		m_BlendRate += 0.1f;
        if (m_Frame >= WALKFlame)
        {
            m_Frame = 0;
        }
	}
	if (ste == Jump)
	{
		m_BlendRate += 0.1f;
        if (m_Frame >= JUMPFlame)
        {
            m_Frame = 0;
        }
	}
    if (ste == Crouchi)
    {
        m_BlendRate += 0.1f;
        if (m_Frame >= CROUCHIFlame)
        {
            m_Frame = 0;
        }
    }
	if (ste == Light_Attack)
	{
		m_BlendRate += 0.1f;
		if (m_Frame >= LAFlame)
		{
			m_Frame = 0;
		}
	}
	if (ste == Medium_Attack)
	{
		m_BlendRate += 0.1f;
		if (m_Frame >= MAFlame)
		{
			m_Frame = 0;
		}
	}
	if (ste == Heavy_Attack)
	{
		m_BlendRate += 0.1f;
		if (m_Frame >= HAFlame)
		{
			m_Frame = 0;
		}
	}
    if (ste == Grap_ready)
    {
        m_BlendRate += 0.1f;
        if (m_Frame >= GRAP_READY_Flame)
        {
            m_Frame = 0;
        }
    }

	if(move)m_Frame++;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;

	old_ste = ste;
}

void EPlayer::PreDraw()
{
	switch (ste)
	{
	case EPlayer::Idle:
		m_Model->Update("Idle", m_Frame, "Idle", m_Frame, m_BlendRate);
		break;
	case EPlayer::Walk:
		m_Model->Update("Idle", m_Frame, "Walk", m_Frame, m_BlendRate);
		break;
	case EPlayer::Jump:
		m_Model->Update("Idle", m_Frame, "Jump", m_Frame, m_BlendRate);
		break;
	case EPlayer::Crouchi:
		m_Model->Update("Idle", m_Frame, "Crouchi", m_Frame, m_BlendRate);
		break;
	case EPlayer::Light_Attack:
		m_Model->Update("Idle", m_Frame, "Light_Attack", m_Frame, m_BlendRate);
		break;
	case EPlayer::Medium_Attack:
		m_Model->Update("Idle", m_Frame, "Medium_Attack", m_Frame, m_BlendRate);
		break;
	case EPlayer::Heavy_Attack:
		m_Model->Update("Idle", m_Frame, "Heavy_Attack", m_Frame, m_BlendRate);
		break;
	case EPlayer::Jump_Attack:
		m_Model->Update("Idle", m_Frame, "Jump_Attack", m_Frame, m_BlendRate);
		break;
	case EPlayer::SP_Attack:
		m_Model->Update("Idle", m_Frame, "SP_Attack", m_Frame, m_BlendRate);
		break;
	case EPlayer::Hit:
		m_Model->Update("Idle", m_Frame, "Hit", m_Frame, m_BlendRate);
		break;
	case EPlayer::Dying:
		m_Model->Update("Idle", m_Frame, "Dying", m_Frame, m_BlendRate);
		break;
	case EPlayer::Win:
		m_Model->Update("Idle", m_Frame, "Win", m_Frame, m_BlendRate);
		break;
	case EPlayer::Guard:
		m_Model->Update("Idle", m_Frame, "Guard", m_Frame, m_BlendRate);
		break;
    case EPlayer::Grap_ready:
        m_Model->Update("Idle", m_Frame, "Grap_ready", m_Frame, m_BlendRate);
        break;
    case EPlayer::Grap_motion:
        m_Model->Update("Idle", m_Frame, "Grap_motion", m_Frame, m_BlendRate);
        break;
	default:
		break;
	}
}
