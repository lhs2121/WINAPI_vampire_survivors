#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

enum class WeaponType;
enum class PassiveType;
class GameEngineRenderer;
class StatusUI : public GameEngineActor
{
public:
	static StatusUI* UI;

	std::vector<WeaponType> MyWeapon;
	std::vector<PassiveType> MyPassive;

	void AddWeaponSlot(WeaponType _Type);
	void UpgradeWeaponSlot(WeaponType _Type);
	void AddMyWeapon(WeaponType _Type);

	void AddPassiveSlot(PassiveType _Type);
	void UpgradePassiveSlot(PassiveType _Type);
	void AddMyPassive(PassiveType _Type);

	bool IsAllMax();
	bool IsFullWeapon();

	bool IsAllMax2();
	bool IsFullpassvie();

	void On() override;
	void Off() override;

	StatusUI() { UI = this; }
	~StatusUI() {}
	StatusUI(const StatusUI& _Other) = delete;
	StatusUI(StatusUI&& _Other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _Other) = delete;
	StatusUI& operator=(StatusUI&& _Other) noexcept = delete;
private:

	GameEngineRenderer* StatsPanel;
	GameEngineRenderer* TopAlpha;
	GameEngineRenderer* BottomAlpha;

	GameEngineRenderer* WeaponChecker[6];
	GameEngineRenderer* PassiveChecker[6];

	std::vector<GameEngineRenderer*> WeaponRenderer;
	std::vector<GameEngineRenderer*> PassiveRenderer;

	int WeaponIndex = 0;
	int PassiveIndex = 0;
	int WeaponUpgradeNum[6] = { 0 };
	int PassiveUpgradeNum[6] = { 0 };

	void Start() override;

};

