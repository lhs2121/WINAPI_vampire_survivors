#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ItemSelectUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemSelectUI()
	{

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
	void SetItemPanel();

private:

	class GameEngineRenderer* ItemSelectPanel;
	class GameEngineRenderer* Text;

	class ItemButton* ItemButton1 = nullptr;
	class ItemButton* ItemButton2 = nullptr;
	class ItemButton* ItemButton3 = nullptr;
	class ItemButton* ItemButton4 = nullptr;

	class GameEngineCollision* Button1;
	class GameEngineCollision* Button2;
	class GameEngineCollision* Button3;
	class GameEngineCollision* Button4;

	class GameEngineCollision* Mouse;

	bool IsLucky = false;
	void Start() override;
	void Update(float _Delta) override;
	
};

