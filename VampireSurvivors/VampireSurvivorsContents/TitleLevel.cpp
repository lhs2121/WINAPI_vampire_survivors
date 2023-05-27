#include "TitleLevel.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include "Image.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}


void TitleLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("introBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("introBG.bmp"));

	}

	Image* image = CreateActor<Image>(0);
}

