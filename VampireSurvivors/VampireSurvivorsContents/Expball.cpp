#include "Expball.h"
#include "Exp.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>


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
}
void Expball::ItemEffect()
{
	Exp::IsTakenExpBall = true;
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
	Player::GetMainPlayer()->AddHP(35);
}



