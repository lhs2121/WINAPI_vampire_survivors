#include "Knife.h"
#include "Enemy.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

float Knife::Speed = 400;
float4 Knife::KnifeDir = float4::RIGHT;

void Knife::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("LKnife.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Weapon\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("LKnife.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("RKnife.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("TKnife.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("BKnife.bmp"));
	}

	{
		Scale = ResourcesManager::GetInst().FindTexture("LKnife.bmp")->GetScale();
		Renderer = CreateRenderer(RenderOrder::Weapon);
		Renderer->SetTexture("RKnife.bmp");

		Collision = CreateCollision(CollisionOrder::Weapon);
		Collision->SetCollisionScale(Scale);

		Off();
	}
}

void Knife::Update(float _Delta)
{
	if (Knife::KnifeDir == float4::UP)
	{
		Renderer->SetTexture("TKnife.bmp");
		Collision->SetCollisionScale({ Scale.Y, Scale.X });
	}
	else if (Knife::KnifeDir == float4::DOWN)
	{
		Renderer->SetTexture("BKnife.bmp");
		Collision->SetCollisionScale({ Scale.Y, Scale.X });
	}
	else if (Knife::KnifeDir == float4::LEFT)
	{
		Renderer->SetTexture("LKnife.bmp");
		Collision->SetCollisionScale(Scale);
	}
	else if (Knife::KnifeDir == float4::RIGHT)
	{
		Renderer->SetTexture("RKnife.bmp");
		Collision->SetCollisionScale(Scale);
	}

	if (true == Collision->Collision(CollisionOrder::Monster, Enemy::AllMonsterCollision, CollisionType::Rect, CollisionType::CirCle))
	{
	    Enemy* FistEnemy = static_cast<Enemy*>(Enemy::AllMonsterCollision[0]->GetActor());
		FistEnemy->SetHp(500);
		
		Enemy::AllMonsterCollision.clear();

		Off();
	}
}
void Knife::On()
{
	GameEngineActor::On();
	Renderer->On();
	Collision->On();
}

void Knife::Off()
{
	GameEngineActor::Off();
	Renderer->Off();
	Collision->Off();
}