#include "Exp.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

void Exp::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Exp_Blue.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Item\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Exp_Blue.bmp"));
	}

	Renderer = CreateRenderer(RenderOrder::Exp);
	Renderer->SetTexture("Exp_Blue.bmp");

	Collision = CreateCollision(CollisionOrder::Exp);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale(CollisionScale);
}
void Exp::Update(float _Delta)
{
	
	if (PlayLevel::AllStop)
	{
		return;
	}

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(),CollisionType::CirCle,CollisionType::CirCle))
	{
		isItemTaken = true;
	}

	if (true == isItemTaken)
	{
		float4 dir = Player::GetMainPlayer()->GetPos() - GetPos();
		dir.Normalize();

		if (OutWardSpeed > 0)
		{
			AddPos(-dir * _Delta * OutWardSpeed);
			OutWardSpeed -= 1;
		}
		else if (OutWardSpeed <= 0)
		{
			AddPos(dir * _Delta * InWardSpeed);
			InWardSpeed += 1;
		}
	}

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion3(), CollisionType::CirCle, CollisionType::CirCle))
	{
		Player::GetMainPlayer()->AddExp(ExpValue);
		Death();
	}
}

void Exp::SetCollisionScale(float4 _Scale)
{
	Collision->SetCollisionScale(_Scale);
}