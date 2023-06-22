#pragma once

enum class UpdateOrder
{
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
	Exp,
	UnderMonster,
	Player,
	UpperMonster,
	Weapon,
	PlayUI,
	Text
};


// ÇïÅ×ÀÌÄ¿ 
enum class CollisionOrder
{
	BackGround,
	Player,
	Monster,
	Weapon,
	Exp,
	PlayUI
};

enum class WeaponType
{
	Knife,
	MagicWand,
	Axe

};