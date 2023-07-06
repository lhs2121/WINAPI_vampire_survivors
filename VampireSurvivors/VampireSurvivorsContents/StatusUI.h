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

	void UpdateWeapon(WeaponType _Type);
	void UpdatePassive(PassiveType _Type);

	bool IsAllMaxWeapon();
	bool IsFullWeapon();

	bool IsAllMaxPassvie();
	bool IsFullPassvie();

	void On() override;
	void Off() override;

	StatusUI() { UI = this; }
	~StatusUI() {}
	StatusUI(const StatusUI& _Other) = delete;
	StatusUI(StatusUI&& _Other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _Other) = delete;
	StatusUI& operator=(StatusUI&& _Other) noexcept = delete;
private:

	GameEngineRenderer* Panel;
	GameEngineRenderer* Alpha;

	std::vector<GameEngineRenderer*> WeaponSlot;
	std::vector<GameEngineRenderer*> PassiveSlot;

	GameEngineRenderer* WeaponUpgrade[6];
	GameEngineRenderer* PassiveUpgrade[6];
	void Start() override;

};

