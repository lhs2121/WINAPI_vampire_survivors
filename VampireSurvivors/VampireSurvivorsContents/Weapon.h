#pragma once


class Weapon
{
public:
	
	Weapon();
	~Weapon();

	
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;



protected:

private:

public:
	static void Knife(float _Delta);
	static void MagicWand(float _Delta);
	static void Axe(float _Delta);
};

