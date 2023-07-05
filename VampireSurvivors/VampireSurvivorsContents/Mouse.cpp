#include "Mouse.h"
#include "ContentsEnum.h"
#include "Expball.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>


Mouse* Mouse::UI;

void Mouse::Start()
{
	Collision = CreateCollision(CollisionOrder::Mouse);
	Collision->SetCollisionScale({ 10,10 });

}


void Mouse::Update(float _Delta)
{
	Collision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());
}
