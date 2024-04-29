#include "PlayerBase.h"

void PlayerBase::Move(GameObject p1)
{

}

void PlayerBase::Push()
{
}

void PlayerBase::SetNowHP(float shp)
{
	this->NowHp = shp;
}

float PlayerBase::GetNowHp()
{
	return this->NowHp;
}

void PlayerBase::DecNowHp(float dmg)
{
	this->NowHp -= dmg;
}

void PlayerBase::Set_Push(bool ph)
{
	Push_Flg = ph;
}

void PlayerBase::Set_status(player_ste st)
{
	ste = st;
}
