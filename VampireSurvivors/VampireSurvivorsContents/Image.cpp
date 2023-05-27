#include "Image.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Image::Image()
{

}

Image::~Image()
{

}
void Image::Start()
{

	SetPos({ 545, 345 });
	Renderer = CreateRenderer(RenderOrder::BackGround);

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("introBG.bmp");
	Renderer->SetTexture("introBG.bmp");
	Renderer->SetRenderScale({1090,690});
	
}