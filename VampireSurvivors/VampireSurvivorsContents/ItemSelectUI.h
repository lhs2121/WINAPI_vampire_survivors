#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ItemSelectUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemSelectUI();
	~ItemSelectUI();

	// delete Function
	ItemSelectUI(const ItemSelectUI& _Other) = delete;
	ItemSelectUI(ItemSelectUI&& _Other) noexcept = delete;
	ItemSelectUI& operator=(const ItemSelectUI& _Other) = delete;
	ItemSelectUI& operator=(ItemSelectUI&& _Other) noexcept = delete;

private:

};

