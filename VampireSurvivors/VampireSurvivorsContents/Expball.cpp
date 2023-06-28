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
void Expball::Update(float _Delta)
{
	Move(_Delta);
	Eat();
}
void Expball::ItemEffect()
{
	Exp::IsTakenExpBall = true;
}

