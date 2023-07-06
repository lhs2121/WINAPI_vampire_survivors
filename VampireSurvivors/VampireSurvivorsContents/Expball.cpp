#include "Expball.h"
#include "ContentsEnum.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>


float Expball::Cooltime = 5;
bool Expball::IsEaten = false;

void Expball::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Exp_ball.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Item\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Exp_ball.bmp"));
	}
	
	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->SetTexture("Exp_ball.bmp");

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale({ 50,50 });

	Cooltime = 5;
}
void Expball::Update(float _Delta)
{
	Move(_Delta);
	Eat();

	if (IsEaten == true)
	{
		Cooltime -= _Delta;

		if (Cooltime < 0)
		{
			IsEaten = false;
			Death();
		}
	}
}
void Expball::Eat()
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		Renderer->Off();
		Collision->Off();
		ItemEffect();
	}
}
void Expball::ItemEffect()
{
	IsEaten = true;
}




void Chicken::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Chicken.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Item\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Chicken.bmp"));
	}

	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->SetTexture("Chicken.bmp");

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale({ 50,50 });
}
void Chicken::ItemEffect()
{
	GameEngineSound::SoundPlay("sfx_gem.ogg");
	Player::GetMainPlayer()->AddHP(70);
}



