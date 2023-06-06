#pragma once
#include <GameEngineCore/GameEngineActor.h>


class TitleBackGround : public GameEngineActor
{
public:
	
	TitleBackGround();
	~TitleBackGround();

	
	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(TitleBackGround&& _Other) noexcept = delete;



protected:

private:

	class GameEngineRenderer* Renderer;


	void Start() override;
};

