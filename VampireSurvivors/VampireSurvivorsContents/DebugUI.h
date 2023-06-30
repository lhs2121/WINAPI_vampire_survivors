#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class DebugUI : public GameEngineActor
{
public:
	static DebugUI* UI;
	float value;
	DebugUI() { UI = this; }
	~DebugUI() {}
	DebugUI(const DebugUI& _Other) = delete;
	DebugUI(DebugUI&& _Other) noexcept = delete;
	DebugUI& operator=(const DebugUI& _Other) = delete;
	DebugUI& operator=(DebugUI&& _Other) noexcept = delete;
private:

	GameEngineRenderer* Renderer;

	void Start() override;
	void Update(float _Delta) override;
};

