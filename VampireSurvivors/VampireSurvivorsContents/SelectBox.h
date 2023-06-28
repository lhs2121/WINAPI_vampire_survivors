#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
enum class WeaponType;
class SelectBox : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectBox()
	{

	}
	~SelectBox()
	{

	}

	void On() override;
	void Off() override;
	void SetWeaponEffect(WeaponType _Type);
	void OnClick();
	
	SelectBox(const SelectBox& _Other) = delete;
	SelectBox(SelectBox&& _Other) noexcept = delete;
	SelectBox& operator=(const SelectBox& _Other) = delete;
	SelectBox& operator=(SelectBox&& _Other) noexcept = delete;

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

