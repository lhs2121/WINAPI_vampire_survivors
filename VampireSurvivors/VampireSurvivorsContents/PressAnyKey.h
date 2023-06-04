#pragma once
#include <GameEngineCore/GameEngineActor.h>


class PressAnyKey : public GameEngineActor
{
public:
	
	PressAnyKey();
	~PressAnyKey();

	
	PressAnyKey(const PressAnyKey& _Other) = delete;
	PressAnyKey(PressAnyKey&& _Other) noexcept = delete;
	PressAnyKey& operator=(const PressAnyKey& _Other) = delete;
	PressAnyKey& operator=(PressAnyKey&& _Other) noexcept = delete;



protected:

private:
	class GameEngineRenderer* Renderer;

	void Start() override;
};

