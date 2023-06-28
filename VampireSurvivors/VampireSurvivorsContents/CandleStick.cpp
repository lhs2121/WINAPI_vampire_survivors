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
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		DropItem();
		Death();
	}
}

void CandleStick::DropItem()
{
	PlayLevel* level = static_cast<PlayLevel*>(GetLevel());
	GameEngineActor* item = level->CreateActor<Expball>();
	item->SetPos(GetPos());
}
