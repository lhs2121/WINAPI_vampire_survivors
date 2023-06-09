#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MenuLevel : public GameEngineLevel
{
public:

	MenuLevel();
	~MenuLevel();


	MenuLevel(const MenuLevel& _Other) = delete;
	MenuLevel(MenuLevel&& _Other) noexcept = delete;
	MenuLevel& operator=(const MenuLevel& _Other) = delete;
	MenuLevel& operator=(MenuLevel&& _Other) noexcept = delete;



protected:

private:

	void Start() override;
	void Update(float _delta) override;

	class imageUI* BackGround = nullptr;
	class SelectPanel* SPanel = nullptr;

	class CharactorButton* ZenaroButton = nullptr;

	class Button* StartButton = nullptr;
	class Button* CollectionButton = nullptr;
	class Button* UpgradeButton = nullptr;
	class Button* MakersButton = nullptr;
	class Button* UnlockButton = nullptr;
};

