#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class PauseUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PauseUI();
	~PauseUI();

	// delete Function
	PauseUI(const PauseUI& _Other) = delete;
	PauseUI(PauseUI&& _Other) noexcept = delete;
	PauseUI& operator=(const PauseUI& _Other) = delete;
	PauseUI& operator=(PauseUI&& _Other) noexcept = delete;

private:

};

