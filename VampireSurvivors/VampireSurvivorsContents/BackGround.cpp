#include "BackGround.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>	
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"
BackGround::BackGround()
{

}
BackGround::~BackGround()
{

}

void BackGround::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("dummy1.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("dummy1.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Debugdummy1.bmp"));

	}

	Scale = ResourcesManager::GetInst().FindTexture("dummy1.bmp")->GetScale();
	OffSetX = float4(Scale.X, 0);
	OffSetY = float4(0, Scale.Y);

	{
		Renderer = CreateRenderer(RenderOrder::BackGround);
		DebugRenderer = CreateRenderer(RenderOrder::BackGround);

		LeftRenderer = CreateRenderer(RenderOrder::BackGround);
		LeftRenderer->SetTexture("dummy1.bmp");
		LeftRenderer->SetRenderPos(Renderer->GetRenderPos() - OffSetX);

		RightRenderer = CreateRenderer(RenderOrder::BackGround);
		RightRenderer->SetTexture("dummy1.bmp");
		RightRenderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);
	}
	

	{
		LeftWall = CreateCollision(CollisionOrder::BackGround);
		LeftWall->SetCollisionPos(-OffSetX.Half());
		LeftWall->SetCollisionScale({ 10,OffSetY.Y });

		RightWall = CreateCollision(CollisionOrder::BackGround);
		RightWall->SetCollisionPos(OffSetX.Half());
		RightWall->SetCollisionScale({ 10,OffSetY.Y });
	}

	SetPos({ 1024,464 });

	Renderer->On();
	DebugRenderer->Off();

}

void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	{
		Renderer->SetTexture(_FileName);
		DebugRenderer->SetTexture(_DebugFileName);
		DebugRenderer->SetRenderScale(Texture->GetScale());
	}
}

void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}


void BackGround::BackGroundLoop()
{
	GameEngineCollision* PlayerCol = Player::GetMainPlayer()->GetCollsion();

	static bool IsCheckingLeft = false; //지금 왼쪽벽과 충돌중인지 체크
	static bool IsCheckingRight = false; //지금 오른쪽벽과 충돌중인지 체크

	if (PlayerCol->CollisonCheck(LeftWall, CollisionType::CirCle, CollisionType::Rect))
	{
		if (IsCheckingLeft == false)
		{
			MoveRendererLeft();
			IsCheckingLeft = true;
		}
	}
	else if (true == IsCheckingLeft && false == PlayerCol->CollisonCheck(LeftWall, CollisionType::CirCle, CollisionType::Rect))
	{

		float4 playerpos = Player::GetMainPlayer()->GetPos();
		float4 wallpos = GetPos() + LeftWall->GetCollisionPos();
		float4 dir = playerpos - wallpos;

		if (dir.X < 0) //왼쪽벽에서 나왔는데 플레이어가 왼쪽에있다면
		{
			MoveCollisionLeft();
		}
		else if (dir.X > 0)//왼쪽벽에서 나왔는데 플레이어가 오른쪽에있다면
		{
			MoveRendererRight();
		}

		IsCheckingLeft = false;
	}

	if (PlayerCol->CollisonCheck(RightWall, CollisionType::CirCle, CollisionType::Rect))
	{
		if (IsCheckingRight == false)
		{
			MoveRendererRight();
			IsCheckingRight = true;
		}
	}
	else if (true == IsCheckingRight && false == PlayerCol->CollisonCheck(RightWall, CollisionType::CirCle, CollisionType::Rect))
	{
		float4 playerpos = Player::GetMainPlayer()->GetPos();
		float4 wallpos = GetPos() + RightWall->GetCollisionPos();
		float4 dir = playerpos - wallpos;

		if (dir.X < 0) //오른쪽벽에서 나왔는데 플레이어가 왼쪽에있다면
		{
			MoveRendererLeft();
		}
		else if (dir.X > 0)//오른쪽벽에서 나왔는데 플레이어가 오른쪽에있다면
		{
			MoveCollisionRight();
		}

		IsCheckingRight = false;
	}
}

void BackGround::MoveRendererRight()
{
	Renderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);
	DebugRenderer->SetRenderPos(Renderer->GetRenderPos());

	LeftRenderer->SetRenderPos(Renderer->GetRenderPos() - OffSetX);
	RightRenderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);
}

void BackGround::MoveRendererLeft()
{
	Renderer->SetRenderPos(Renderer->GetRenderPos() + (-OffSetX));
	DebugRenderer->SetRenderPos(Renderer->GetRenderPos());

	LeftRenderer->SetRenderPos(Renderer->GetRenderPos() - OffSetX);
	RightRenderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);
}

void BackGround::MoveCollisionLeft()
{
	LeftWall->SetCollisionPos(LeftWall->GetCollisionPos() - OffSetX);
	RightWall->SetCollisionPos(RightWall->GetCollisionPos() - OffSetX);
}
void BackGround::MoveCollisionRight()
{
	LeftWall->SetCollisionPos(LeftWall->GetCollisionPos() + OffSetX);
	RightWall->SetCollisionPos(LeftWall->GetCollisionPos() + OffSetX);
}
