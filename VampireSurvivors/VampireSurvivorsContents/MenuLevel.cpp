#include "MenuLevel.h"
#include "IntroImage.h"
#include "CharactorSelectUI.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

MenuLevel::MenuLevel()
{

}

MenuLevel::~MenuLevel()
{

}


void MenuLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("start.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\MenuScene\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("start.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("collection.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("upgrade.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("unlock.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("makers.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("SelectPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Zenaro.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Imelda.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LFocusCursor.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("RFocusCursor.bmp"), 6, 1);
	}

	CreateActor<IntroImage>(0);
	CreateActor<CharactorSelectUI>(0);

}

void MenuLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}
}

