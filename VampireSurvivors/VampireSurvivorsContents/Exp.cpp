#include "Exp.h"
#include "Expball.h"
#include "ContentsEnum.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineSound.h>

float4 Exp::Scale = {40,40};
float Exp::expValue = 50;

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

	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->SetTexture("Exp_Blue.bmp");

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale(Scale);
}
void Exp::Update(float _Delta)
{
	if (false == Expball::IsEaten)
	{
		Move(_Delta);
	}
	else if (true == Expball::IsEaten)
	{
		dir = Player::GetMainPlayer()->GetPos() - GetPos();
		dir.Normalize();
		AddPos(dir * 300 * _Delta);
	}

	Eat();
}
void Exp::ItemEffect()
{
	GameEngineSound::SoundPlay("sfx_gem.ogg");
	
	Player::GetMainPlayer()->AddExp(expValue);
}

void Exp::Eat()
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		ItemEffect();
		Death();
	}
}
