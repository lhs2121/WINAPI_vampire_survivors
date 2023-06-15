#include "Knife.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

void Knife::Start()
{
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Weapon\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Knife.bmp"));
	}
	{
		float4 Scale = ResourcesManager::GetInst().FindTexture("Knife.bmp")->GetScale();
		Renderer = CreateRenderer(RenderOrder::Weapon);
		Renderer->SetTexture("Knife.bmp");

		Collision = CreateCollision(CollisionOrder::Weapon);
		Collision->SetCollisionScale(Scale);

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