#pragma once

enum class UpdateOrder
{
	BackGround,
	Player,
	Monster,
	Item,
	Weapon,
	PlayUI
};

enum class RenderOrder
{
	BackGround,
	UnderMonster,
	Player,
	UpperMonster,
	Weapon,
	Exp,
	PlayUI,
	Text
};


// ÇïÅ×ÀÌÄ¿ 
enum class CollisionOrder
{
	BackGround,
	Player,
	Monster,
	Exp,
	Weapon,
	PlayUI
};

enum class WeaponType
{
	Projectile,

};