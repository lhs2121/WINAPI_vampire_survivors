#pragma once
#include <GameEngineCore/GameEngineLevel.h>
class Button;
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

	class imageUI* BackGroundImg = nullptr;
	class SelectPanel* SPanel = nullptr;

	class CharactorButton* ZenaroButton = nullptr;

	Button* StartButton = nullptr;
	Button* CollectionButton = nullptr;
	Button* UpgradeButton = nullptr;
	Button* MakersButton = nullptr;
	Button* UnlockButton = nullptr;
};

