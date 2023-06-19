#pragma once

enum class UpdateOrder
{
	BackGround,
	Player,
	Weapon,
	Monster,
	
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
	PlayUI2
};

// ÇïÅ×ÀÌÄ¿ 
enum class CollisionOrder
{
	BackGround,
	Player,
	Monster,
	Exp,
	Weapon,
};

enum class WeaponType
{
	Projectile,

};