#include "Enemy.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
void Enemy::Start()
{
	SetPos(float4::ZERO);

	Renderer = CreateRenderer(RenderOrder::UnderMonster);

	Renderer->CreateAnimation("Enemy1Run", "enemy1.bmp", 0, 4, 0.1f, true);
	Renderer->ChangeAnimation("Enemy1Run");
}