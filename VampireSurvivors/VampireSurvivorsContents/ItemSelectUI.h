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
	class GameEngineRenderer* ItemPanel_1;
	class GameEngineRenderer* ItemPanel_2;
	class GameEngineRenderer* ItemPanel_3;


	class GameEngineCollision* Button1;
	class GameEngineCollision* Button2;
	class GameEngineCollision* Button3;
	class GameEngineCollision* Button4;

	class GameEngineCollision* Mouse;


	



	float4 Offset = { -545,-345 };

	void Start() override;
	void Update(float _Delta) override;
	
};

