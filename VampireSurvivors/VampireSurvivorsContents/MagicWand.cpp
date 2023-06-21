#include "MagicWand.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>


float4 MagicWand::Dir;

void MagicWand::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("MagicWand.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Weapon\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("MagicWand_Mask.bmp"));

		GameEngineSprite* sprite = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("MagicWand.bmp"), 2, 1);
		sprite->SetMaskTexture("MagicWand_Mask.bmp");

	}

	Renderer = CreateRenderer(RenderOrder::Weapon);
	Renderer->CreateAnimation("MagicWand", "MagicWand.bmp", 0, 1, 0.5f, true);
	Renderer->ChangeAnimation("MagicWand");

	Collision = CreateCollision(CollisionOrder::Weapon1);
	Collision->SetCollisionScale({ 30,30 });


	Off();

}

void MagicWand::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	std::vector<GameEngineCollision*> result;

	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		Enemy* e = static_cast<Enemy*>(result[0]->GetActor());
		e->ApplyDamage(50);
		Off();
	}
}

void MagicWand::On()
{
	GameEngineActor::On();
	Renderer->On();
	Collision->On();
}

void MagicWand::Off()
{
	GameEngineActor::Off();
	Renderer->Off();
	Collision->Off();
}

void MagicWand::SetAngle(float _Angle)
{
	Renderer->SetAngle(_Angle);
}