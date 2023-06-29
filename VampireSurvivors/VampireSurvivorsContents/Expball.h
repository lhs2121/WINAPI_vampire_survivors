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
	void ItemEffect() override;
};

class Chicken : public Item
{
public:

	Chicken() {}
	~Chicken() {}

	Chicken(const Chicken& _Other) = delete;
	Chicken(Chicken&& _Other) noexcept = delete;
	Chicken& operator=(const Chicken& _Other) = delete;
	Chicken& operator=(Chicken&& _Other) noexcept = delete;


private:
	void Start() override;
	void ItemEffect() override;
};

