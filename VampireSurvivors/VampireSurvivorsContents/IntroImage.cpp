#include "IntroImage.h"
#include <GameEngineCore/GameEngineRenderer.h>

void IntroImage::Start()
{
	SetPos({ 545,345 });

	Renderer = CreateRenderer(0);
	Renderer->SetTexture("introBG.bmp");
}