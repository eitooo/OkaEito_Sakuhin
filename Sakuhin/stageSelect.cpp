#include "stageSelect.h"

#include "field.h"
#include "wall.h"

void stageSelect::Init()
{
	{
		Field* field = AddGameObject<Field>(1);
		field->SetPosition(DirectX::SimpleMath::Vector3::Vector3(0.0f, 0.0f, 0.0f));

		Wall* wall = AddGameObject<Wall>(1);
		wall->SetPosition(DirectX::SimpleMath::Vector3::Vector3(0.0f, 0.0f, 0.0f));
	}
		

	
	
}

void stageSelect::Uninit()
{
}

void stageSelect::Update()
{

}
