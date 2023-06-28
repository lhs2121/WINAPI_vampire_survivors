#include "Item.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>


void Item::Move(float _Delta)
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		isItemTaken = true;
	}

	if (true == isItemTaken)
	{
		dir = Player::GetMainPlayer()->GetPos() - GetPos();
		dir.Normalize();

		if (OutWardSpeed > 0)
		{
			AddPos(-dir * _Delta * OutWardSpeed);
			OutWardSpeed -= 1 * 700 * _Delta;
		}
		else if (OutWardSpeed <= 0)
		{
			AddPos(dir * _Delta * InWardSpeed);
			InWardSpeed += 1 * 700 * _Delta;
		}
	}
}

void Item::Eat()
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		ItemEffect();
		Death();
	}
}

void Item::ItemEffect()
{

}