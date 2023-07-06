#pragma once

enum class CharacterType
{
	Zenaro,
	Imelda
};

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


// ÇïÅ×ÀÌÄ¿ 
enum class CollisionOrder
{
	BackGround,
	Player, 
	Weapon,
	Monster,
	Boss,
	Item,
	PlayUI,
	Mouse
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

enum class PassiveType
{
	Blackheart,
	Redheart,
	Book,
	Glove,
	Candle,
	Expball,
	Crown,
	Spinach,
	Wing,
	Clover,
	Chicken,
	Money,
	Null
};
