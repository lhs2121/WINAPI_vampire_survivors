#pragma once

enum class UpdateOrder
{
	Timer,
	BackGround,
	Weapon,
	Player,
	Monster,
	Item,
	PlayUI
};

enum class RenderOrder
{
	BackGround,
	UnderMonster,
	Player,
	UpperMonster,
	Item,
	Weapon,
	PlayUI,
	Text
};


// ������Ŀ 
enum class CollisionOrder
{
	BackGround,
	Player,
	Monster,
	Weapon,
	Item,
	PlayUI
};

enum class WeaponType
{
	Knife,
	MagicWand,
	Axe,
	Runetracer,
	FireWand,
	Cross,
	Whip,
	Null
	
};

