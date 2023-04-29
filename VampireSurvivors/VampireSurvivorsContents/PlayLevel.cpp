#include "PlayLevel.h"
#include "Player.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	// 플레이 레벨이 만들어졌다.
	// 이 레벨에는 뭐가 있어야지?
	// 플레이어 만들고
	// 맵만들고
	// 몬스터 만들고
	// 액터

	// 자기 임의대로 만들겠다는 것이고 xxxxx
	// Player* NewPlayer = new Player();

	CreateActor<Player>();
}


void PlayLevel::Update()
{
}
void PlayLevel::Render()
{
}
void PlayLevel::Release()
{
}