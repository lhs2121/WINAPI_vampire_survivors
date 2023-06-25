#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
	void SetTexture();
	void On() override;
	void Off() override;
	void OnClick();
	// delete Function
	ItemButton(const ItemButton& _Other) = delete;
	ItemButton(ItemButton&& _Other) noexcept = delete;
	ItemButton& operator=(const ItemButton& _Other) = delete;
	ItemButton& operator=(ItemButton&& _Other) noexcept = delete;

private:

	class GameEngineRenderer* Panel;
	class GameEngineRenderer* WeaponNameText;
	class GameEngineRenderer* NewText;
	class GameEngineRenderer* DetailText;

	int Curlevel;
	WeaponType CurType;
	
	void Start() override;
	void Update(float _Delta) override;

};

