#include "Knife.h"
#include "Enemy.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

float Knife::Speed = 400;
float4 Knife::Dir = float4::RIGHT;

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

		Collision = CreateCollision(CollisionOrder::Weapon1);
		Collision->SetCollisionScale(Scale);

		Off();
	}
}

void Knife::Update(float _Delta)
{

	AddPos(Dir * _Delta * Speed);

	if (Dir == float4::UP)
	{
		Renderer->SetTexture("TKnife.bmp");
		Collision->SetCollisionScale({ Scale.Y, Scale.X });
	}
	else if (Dir == float4::DOWN)
	{
		Renderer->SetTexture("BKnife.bmp");
		Collision->SetCollisionScale({ Scale.Y, Scale.X });
	}
	else if (Dir == float4::LEFT)
	{
		Renderer->SetTexture("LKnife.bmp");
		Collision->SetCollisionScale(Scale);
	}
	else if (Dir == float4::RIGHT)
	{
		Renderer->SetTexture("RKnife.bmp");
		Collision->SetCollisionScale(Scale);
	}

	std::vector<GameEngineCollision*> result;

	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		Enemy* e = static_cast<Enemy*>(result[0]->GetActor());
		e->ApplyDamage(50);
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