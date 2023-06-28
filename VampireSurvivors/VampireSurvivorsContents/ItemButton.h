#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
enum class WeaponType;
class ItemButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemButton()
	{

	}
	~ItemButton()
	{

	}

	void On() override;
	void Off() override;
	void SetWeaponEffect(WeaponType _Type);
	void OnClick();
	
	ItemButton(const ItemButton& _Other) = delete;
	ItemButton(ItemButton&& _Other) noexcept = delete;
	ItemButton& operator=(const ItemButton& _Other) = delete;
	ItemButton& operator=(ItemButton&& _Other) noexcept = delete;

private:
	class GameEngineRenderer* Panel;
	class GameEngineRenderer* WeaponNameText;
	class GameEngineRenderer* NewText;
	class GameEngineRenderer* DetailText;
	class GameEngineRenderer* DetailText2;

	int Curlevel;
	WeaponType CurType;

	int _Count = 0;
	float _Speed = 0;
	float _Damage = 0;
	float _DeathTime = 0;
	float _CoolTime = 0;
	float _Interval = 0;
	float4 _Scale = float4::ZERO;

	void Start() override;





};

