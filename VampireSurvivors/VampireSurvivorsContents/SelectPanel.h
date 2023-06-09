#pragma once
#include "imageUI.h"
#include <vector>
class SelectPanel : public imageUI
{

public:

	SelectPanel()
	{};
	~SelectPanel()
	{};


	SelectPanel(const SelectPanel& _Other) = delete;
	SelectPanel(SelectPanel&& _Other) noexcept = delete;
	SelectPanel& operator=(const SelectPanel& _Other) = delete;
	SelectPanel& operator=(SelectPanel&& _Other) noexcept = delete;


	void SetButton(GameEngineActor* _Button);
	
	void Off() override;

protected:

private:
	void Start() override;

	void On() override;

	std::vector<GameEngineActor*> CharactorButton;

	
};

