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

	SetPos(float4::ZERO);

	Renderer = CreateRenderer(RenderOrder::BackGround);
	DebugRenderer = CreateRenderer(RenderOrder::BackGround);

	Renderer->On();
	DebugRenderer->Off();

	for (int i = 0; i < 2; i++)
	{
		OtherRendererGroup[i] = CreateRenderer(RenderOrder::BackGround);
		OtherRendererGroup[i]->SetTexture("dummy1.bmp");
	}

	{
		LeftWall = CreateCollision(CollisionOrder::BackGround);
		LeftWall->SetCollisionPos(-OffSetX.Half());
		LeftWall->SetCollisionScale(OffSetY);

		RightWall = CreateCollision(CollisionOrder::BackGround);
		RightWall->SetCollisionPos(OffSetX.Half());
		RightWall->SetCollisionScale(OffSetY);
	}

	MoveOtherRenderer();
}

void BackGround::Update(float _Delta)
{



}

void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Scale = Texture->GetScale();
	FileName = _FileName;
	{
		Renderer->SetTexture(FileName);
		DebugRenderer->SetTexture(_DebugFileName);
		DebugRenderer->SetRenderScale(Scale);
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


void BackGround::BackGroundLoop(Player* player)
{

	GameEngineCollision* PlayerCol = Player::GetMainPlayer()->GetCollsion();

	if (RightWall->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::CirCle))//플레이어가 오른쪽벽에 닿았을때
	{
		if (OnCollision == false)
		{
			MoveRight();

			RightWallCheck = true;
			LeftWallCheck = false;
			OnCollision = true;
		}
	}

	else if (LeftWall->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::CirCle)) //플레이어가 왼쪽벽에 닿았을때
	{

		if (OnCollision == false)
		{
			MoveLeft();

			LeftWallCheck = true;
			RightWallCheck = false;
			OnCollision = true;
		}
	}

	else if (false == RightWall->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::CirCle) &&
		false == LeftWall->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::CirCle) &&
		true == OnCollision) //플레이어가 벽에서 벗어났을 때
	{
		if (true == RightWallCheck) //이전프레임 에서 오른쪽벽과 충돌하고 있었다면
		{
			float4 dir = Player::GetMainPlayer()->GetPos() - LeftWall->GetCollisionPos();

			if (dir.X < 0)
			{
				MoveLeft();
			}
		}
		else if (true == LeftWallCheck) //이전프레임 에서 왼벽과 충돌하고 있었다면
		{
			float4 dir = Player::GetMainPlayer()->GetPos() - RightWall->GetCollisionPos();

			if (dir.X > 0)
			{
				MoveRight();
			}
		}

		LeftWallCheck = false;
		RightWallCheck = false;
		OnCollision = false;
	}
}

void BackGround::MoveRight()
{
	Renderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);
	DebugRenderer->SetRenderPos(Renderer->GetRenderPos());

	LeftWall->SetCollisionPos(LeftWall->GetCollisionPos() + OffSetX);
	RightWall->SetCollisionPos(RightWall->GetCollisionPos() + OffSetX);
	MoveOtherRenderer();
}

void BackGround::MoveLeft()
{
	Renderer->SetRenderPos(Renderer->GetRenderPos() + (-OffSetX));
	DebugRenderer->SetRenderPos(Renderer->GetRenderPos());

	LeftWall->SetCollisionPos(LeftWall->GetCollisionPos() + (-OffSetX));
	RightWall->SetCollisionPos(RightWall->GetCollisionPos() + (-OffSetX));
	MoveOtherRenderer();
}

void BackGround::MoveOtherRenderer()
{
	OtherRendererGroup[0]->SetRenderPos(Renderer->GetRenderPos() + float4(-Scale.X, 0));
	OtherRendererGroup[1]->SetRenderPos(Renderer->GetRenderPos() + float4(Scale.X, 0));

}

