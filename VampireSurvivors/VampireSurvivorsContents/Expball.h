#pragma once
#include "Item.h"
class Expball : public Item
{
public:

	Expball() {}
	~Expball() {}

	Expball(const Expball& _Other) = delete;
	Expball(Expball&& _Other) noexcept = delete;
	Expball& operator=(const Expball& _Other) = delete;
	Expball& operator=(Expball&& _Other) noexcept = delete;


private:
	void Start() override;
	void Update(float _Delta) override;
	void ItemEffect() override;
};

