#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

class GameEngineRenderer;
class ItemButton;
class GameEngineCollision;
enum class WeaponType;
class ItemSelectUI : public GameEngineActor
{
public:

	static ItemSelectUI* SelectUI;
	// constrcuter destructer
	ItemSelectUI()
	{
		SelectUI = this;
	}
	~ItemSelectUI()
	{

	}

	// delete Function
	ItemSelectUI(const ItemSelectUI& _Other) = delete;
	ItemSelectUI(ItemSelectUI&& _Other) noexcept = delete;
	ItemSelectUI& operator=(const ItemSelectUI& _Other) = delete;
	ItemSelectUI& operator=(ItemSelectUI&& _Other) noexcept = delete;

	void On() override;
	void Off() override;

	void WeaponSlotUpgrade(WeaponType _Type);
	void CreateWeaponSlotRenderer(WeaponType _Type);
private:
	int WeaponNum = 0;
	int AccessoryNum = 0;

	int WeaponUpgradeNum[6] = { 0 };

	GameEngineRenderer* ItemSelectPanel;
	GameEngineRenderer* Text;
	GameEngineRenderer* StatsPanel;
	GameEngineRenderer* TopAlpha;
	GameEngineRenderer* BottomAlpha;


	std::vector<GameEngineRenderer*> WeaponRenderer;
	std::vector<GameEngineRenderer*> AccessoryRenderer;

	GameEngineRenderer* WeaponChecker[6];
	GameEngineRenderer* AccessoryChecker[6];

	ItemButton* ItemButton1 = nullptr;
	ItemButton* ItemButton2 = nullptr;
	ItemButton* ItemButton3 = nullptr;
	ItemButton* ItemButton4 = nullptr;

	GameEngineCollision* Button1;
	GameEngineCollision* Button2;
	GameEngineCollision* Button3;
	GameEngineCollision* Button4;

	GameEngineCollision* Mouse;

	bool IsLucky = false;
	void Start() override;
	void Update(float _Delta) override;
	

};

