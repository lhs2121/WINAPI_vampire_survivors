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
	}

	Renderer = CreateRenderer(RenderOrder::Item);
	Renderer->SetTexture("Box.bmp");

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