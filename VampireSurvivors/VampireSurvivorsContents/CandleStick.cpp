#include "CandleStick.h"
#include "ContentsEnum.h"
#include "Expball.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>


void CandleStick::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Bigcandle.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Item\\");
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Bigcandle.bmp"), 3, 1);
	}

	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->CreateAnimation("Bigcandle", "Bigcandle.bmp", 0, 2, 0.1f, true);
	Renderer->ChangeAnimation("Bigcandle");

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale({ 50,50 });
}
void CandleStick::Update(float _Delta)
{
	if (IsEaten == true)
	{
		Cooltime -= _Delta;
	}
	else
	{
		if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
		{
			DropItem();
			Renderer->Off();
			Collision->Off();
			IsEaten = true;
		}
	}

	if (Cooltime <= 0)
	{
		float value = GameEngineRandom::MainRandom.RandomFloat(-30, 30);
		SetPos(GetPos() + float4(value, 0));
		IsEaten = false;
		Cooltime = 20;
		Renderer->On();
		Collision->On();
	}
}

void CandleStick::DropItem()
{
	int random = GameEngineRandom::MainRandom.RandomInt(1, 100);

	if (random > 50)
	{
		PlayLevel* level = static_cast<PlayLevel*>(GetLevel());
		GameEngineActor* item = level->CreateActor<Expball>();
		item->SetPos(GetPos());
	}
	else if(random <= 50)
	{
		PlayLevel* level = static_cast<PlayLevel*>(GetLevel());
		GameEngineActor* item = level->CreateActor<Chicken>();
		item->SetPos(GetPos());
	}
	
}
