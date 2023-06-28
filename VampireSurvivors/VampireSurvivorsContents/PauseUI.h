#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PauseUI : public GameEngineActor
{
public:

	PauseUI();
	~PauseUI();

	PauseUI(const PauseUI& _Other) = delete;
	PauseUI(PauseUI&& _Other) noexcept = delete;
	PauseUI& operator=(const PauseUI& _Other) = delete;
	PauseUI& operator=(PauseUI&& _Other) noexcept = delete;

private:

};

