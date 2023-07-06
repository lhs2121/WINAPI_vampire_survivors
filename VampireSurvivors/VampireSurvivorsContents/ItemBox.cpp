#include "ItemBox.h"
#include "LevelUpUI.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

void ItemBox::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Box.bmp"))
	{
		GameEnginePath path;

		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Item\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Box.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("BoxFocusCursor.bmp"), 6, 1);
	}

	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->SetTexture("Box.bmp");

	Cursor = CreateRenderer(RenderOrder::Item);
	Cursor->CreateAnimation("BoxCursor", "BoxFocusCursor.bmp", 0, 5, 0.1f, true);
	Cursor->ChangeAnimation("BoxCursor");
	Cursor->SetRenderScale({ 40,40 });
	Cursor->SetRenderPos(float4(0, -35));

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetCollisionType(CollisionType::CirCle);
	Collision->SetCollisionScale({ 50,50 });
}

void ItemBox::Update(float _Delta)
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		LevelUpUI::UI->OnBox();
		Death();
	}


}