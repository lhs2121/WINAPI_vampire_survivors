#include "IntroLevel.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "imageUI.h"
#include "PressAnyKey.h"
IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}


void IntroLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("introBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\MenuScene\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("introBG.bmp"));

	}

	CreateActor<imageUI>(0)->Init("introBG.bmp");

	CreateActor<PressAnyKey>(1);

	
}

void IntroLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN))
	{

		GameEngineCore::ChangeLevel("MenuLevel");
		
	} 

}

