#include "Button.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <windows.h>

Button::Button()
{

}
Button::~Button()
{

}

void Button::Start()
{

	SetPos({ 545,345 });

}


void Button::Init(const std::string& path, const float4 RenderPos, float Ratio)
{
	GameEngineWindowTexture* texture = ResourcesManager::GetInst().FindTexture(path);
	Renderer = CreateRenderer(RenderOrder::PlayUI);
	Renderer->SetTexture(path);
	Renderer->SetRenderPos(RenderPos);
	Renderer->SetRenderScale(texture->GetScale() * Ratio);

	Scale = texture->GetScale() * Ratio;

}

bool Button::CheckCollision(float left, float right, float top, float bottom, int mouseX, int mouseY)
{
	if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom)
	{
		return true;
	}
	return false;
}

void Button::Update(float _delta)
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GameEngineWindow::MainWindow.GetHWND(), &mousePos);

		float left = Renderer->GetScreenPos().X - Scale.hX();
		float Right = Renderer->GetScreenPos().X + Scale.hX();
		float Top = Renderer->GetScreenPos().Y - Scale.hY();
		float Bottom = Renderer->GetScreenPos().Y + Scale.hY();

		if (true == CheckCollision(left, Right, Top, Bottom, mousePos.x, mousePos.y))
		{
			if (Panel != nullptr)
			{
				if (false == Panel->GetRenderer()->IsUpdate())
				{
					Panel->GetRenderer()->On();
				}
			}
		}

	}


}

