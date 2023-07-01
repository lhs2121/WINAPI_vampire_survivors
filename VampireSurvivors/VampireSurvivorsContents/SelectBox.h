#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "ContentsEnum.h"
class PassiveStats;
class SelectBox : public GameEngineActor
{
public:
	static bool IsChickenSelected;
	static bool IsMoneySelected;

	void SetEffect(WeaponType _Type = WeaponType::Null, PassiveType _Type2 = PassiveType::Null);
	void OnClick();
	void SetWeaponEffect();
	void SetPassiveEffect();

	void On() override;
	void Off() override;

	SelectBox() {}
	~SelectBox() {}
	SelectBox(const SelectBox& _Other) = delete;
	SelectBox(SelectBox&& _Other) noexcept = delete;
	SelectBox& operator=(const SelectBox& _Other) = delete;
	SelectBox& operator=(SelectBox&& _Other) noexcept = delete;

private:
	int CurWeaponLevel;
	int CurPassiveLevel;

	WeaponType CurWeaponType;
	PassiveType CurPassiveType;

	bool IsWeaponButton = false;
	bool IsEmptyEffect = false;

	int _Count = 0;
	float _Speed = 0;
	float _Damage = 0;
	float _DeathTime = 0;
	float _CoolTime = 0;
	float _Interval = 0;
	float _ScaleRatio = 0;

	class GameEngineRenderer* Panel;
	class GameEngineRenderer* WeaponNameText;
	class GameEngineRenderer* NewText;
	class GameEngineRenderer* DetailText;
	class GameEngineRenderer* DetailText2;

	void Start() override;
};

