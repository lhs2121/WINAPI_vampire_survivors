#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

enum class WeaponType;
class GameEngineRenderer;
class StatusUI : public GameEngineActor
{
public:
	static StatusUI* UI;

	StatusUI() { UI = this; }
	~StatusUI() {}
	StatusUI(const StatusUI& _Other) = delete;
	StatusUI(StatusUI&& _Other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _Other) = delete;
	StatusUI& operator=(StatusUI&& _Other) noexcept = delete;

	std::vector<WeaponType> MyWeapon;

	void AddWeaponSlot(WeaponType _Type);
	void UpgradeWeaponSlot(WeaponType _Type);
	void AddMyWeapon(WeaponType _Type);

	bool IsAllMax();
	bool IsFullWeapon();

	void On() override;
	void Off() override;
private:

	GameEngineRenderer* StatsPanel;
	GameEngineRenderer* TopAlpha;
	GameEngineRenderer* BottomAlpha;

	GameEngineRenderer* WeaponChecker[6];
	GameEngineRenderer* AccessoryChecker[6];

	std::vector<GameEngineRenderer*> WeaponRenderer;
	std::vector<GameEngineRenderer*> AccessoryRenderer;

	int WeaponIndex = 0;
	int AccessoryIndex = 0;
	int WeaponUpgradeNum[6] = { 0 };

	void Start() override;

};

