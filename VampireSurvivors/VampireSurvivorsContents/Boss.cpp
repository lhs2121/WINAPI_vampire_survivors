#include "Boss.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>


void Boss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Boss_left.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_left.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_right.bmp"), 4, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_death_left.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_death_right.bmp"), 10, 1);
	}

	Renderer = CreateRenderer(RenderOrder::UnderMonster);
	Renderer->CreateAnimation("Boss_Left", "Boss_left.bmp", 0,3);
	Renderer->CreateAnimation("Boss_Right", "Boss_right.bmp", 0, 3);
	Renderer->ChangeAnimation("Boss_Left");

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetCollisionScale({ 20,20 });
	Collision->SetCollisionType(CollisionType::CirCle);

	SetPos(float4(Player::GetMainPlayer()->GetPos().X,454) + float4(550, 0));

}

void Boss::Update(float _Delta)
{
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();
	AddPos(dir * _Delta * 150);

	if (Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		Player::GetMainPlayer()->ApplyDamage(20);
		hp -= 10;
	}

	if (Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		float4 dir2 = Player::GetMainPlayer()->GetPos() - GetPos();
		dir2.Normalize();

		AddPos(dir2 * _Delta * 500);
	}

	if (hp < 0)
	{
		Death();
	}
}