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
		Left = CreateCollision(CollisionOrder::BackGround);
		Left->SetCollisionPos(-OffSetX.Half());
		Left->SetCollisionScale(OffSetY);

		Right = CreateCollision(CollisionOrder::BackGround);
		Right->SetCollisionPos(OffSetX.Half());
		Right->SetCollisionScale(OffSetY);
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

	if (Right->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::Rect))
	{
		if (OnCollision == false)
		{
			Renderer->SetRenderPos(Renderer->GetRenderPos() + OffSetX);

			Left->SetCollisionPos(Left->GetCollisionPos() + OffSetX);
			Right->SetCollisionPos(Right->GetCollisionPos() + OffSetX);
			MoveOtherRenderer();

			OnCollision = true;
		}
		
	}
	else if (Left->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::Rect))
	{

		if (OnCollision == false)
		{
			Renderer->SetRenderPos(Renderer->GetRenderPos() + (-OffSetX));

			Left->SetCollisionPos(Left->GetCollisionPos() + (-OffSetX));
			Right->SetCollisionPos(Right->GetCollisionPos() + (-OffSetX));
			MoveOtherRenderer();

			OnCollision = true;
		}
		
	}
	else if (false == Right->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::Rect) &&
		false == Left->CollisonCheck(PlayerCol, CollisionType::Rect, CollisionType::Rect) &&
		true == OnCollision)
	{
		OnCollision = false;
	}
}

void BackGround::MoveOtherRenderer()
{
	OtherRendererGroup[0]->SetRenderPos(Renderer->GetRenderPos() + float4(-Scale.X, 0));
	OtherRendererGroup[1]->SetRenderPos(Renderer->GetRenderPos() + float4(Scale.X, 0));

}