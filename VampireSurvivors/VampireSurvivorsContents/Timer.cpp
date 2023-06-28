#include "Timer.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <sstream>
#include <iomanip>

void Timer::Start()
{
	Text_Timer = CreateUIRenderer(RenderOrder::Text);
	Text_Timer->SetText("00:00", 35, "메이플스토리");
	Text_Timer->SetRenderPos({ 490,35 });
}

void Timer::Update(float _Delta)
{
	seconds += _Delta;

	if (seconds > 59.5)
	{
		minutes++;
		seconds = 0;
	}

	std::stringstream time;
	time << std::setfill('0') << std::setw(2) << minutes << ":";
	time << std::fixed << std::setprecision(0) << std::setfill('0') << std::setw(2) << seconds;

	Text_Timer->SetText(time.str(), 35, "메이플스토리");

	if (GameEngineInput::IsDown('K'))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(3);
	}
}