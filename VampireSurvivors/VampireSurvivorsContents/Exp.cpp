#include "Exp.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>


bool Exp::IsTakenExpBall = false;

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
	Collision->SetCollisionScale({50,50});
}
void Exp::Update(float _Delta)
{
	if (true == IsTakenExpBall)
	{
    	dir = Player::GetMainPlayer()->GetPos() - GetPos();
		dir.Normalize();
		AddPos(dir * 300 * _Delta);

		expballtime -= GameEngineTime::MainTimer.GetDeltaTime();

		if (expballtime < 0)
		{
			IsTakenExpBall = false;
			expballtime = 5;
		}
	}
	else if (false == IsTakenExpBall)
	{
		Move(_Delta);
	}

	Eat();
}
void Exp::ItemEffect()
{
	Player::GetMainPlayer()->AddExp(20);
}

