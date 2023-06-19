#include "PlayUIManager.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager() 
{
	UI = this;
}

PlayUIManager::~PlayUIManager() 
{
}

void PlayUIManager::Start() 
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ExpBar.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ExpBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ExpGauge.bmp"));

	}
	ExpBar = CreateUIRenderer(RenderOrder::PlayUI);
	ExpBar->SetTexture("ExpBar.bmp");
	ExpBar->SetRenderPos({ 545,12 });

	ExpGauge = CreateUIRenderer(RenderOrder::PlayUI);
	ExpGauge->SetTexture("ExpGauge.bmp");
	ExpGauge->SetRenderPos({ 545,12 });

}