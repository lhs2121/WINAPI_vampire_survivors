#pragma once

#include "Button.h"

class CharactorButton : public Button
{
public:

	CharactorButton();
	~CharactorButton();


	CharactorButton(const CharactorButton& _Other) = delete;
	CharactorButton(CharactorButton&& _Other) noexcept = delete;
	CharactorButton& operator=(const CharactorButton& _Other) = delete;
	CharactorButton& operator=(CharactorButton&& _Other) noexcept = delete;



protected:


private:
	void OnClick() override;
};

