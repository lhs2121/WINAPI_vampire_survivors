#include "FinalBoss.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>


void FinalBoss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBoss_Left.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("FinalBoss_Left.bmp"), 1, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("FinalBoss_Right.bmp"), 1, 1);
	}

	Renderer = CreateRenderer(RenderOrder::UpperMonster);
	Renderer->CreateAnimation("FinalBoss_Left", "FinalBoss_left.bmp", 0, 0);
	Renderer->CreateAnimation("FinalBoss_Right", "FinalBoss_right.bmp", 0, 0);
	Renderer->ChangeAnimation("FinalBoss_Left");

	Collision = CreateCollision(CollisionOrder::Boss);
	Collision->SetCollisionScale({ 40,40 });
	Collision->SetCollisionType(CollisionType::CirCle);

	int num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (num == 0)
	{
		SetPos(float4(Player::GetMainPlayer()->GetPos().X, 454) + float4(550, GameEngineRandom::MainRandom.RandomFloat(-30, 30)));
	}
	else
	{
		SetPos(float4(Player::GetMainPlayer()->GetPos().X, 454) + float4(-550, GameEngineRandom::MainRandom.RandomFloat(-30, 30)));
	}
}

void FinalBoss::Update(float _Delta)
{
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();

	if (dir.X > 0)
	{
		Renderer->ChangeAnimation("FinalBoss_Right");
	}
	else if (dir.X < 0)
	{
		Renderer->ChangeAnimation("FinalBoss_Left");
	}

	AddPos(dir * _Delta * 200);

}
