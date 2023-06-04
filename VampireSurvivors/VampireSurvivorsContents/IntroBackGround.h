#pragma once
#include <GameEngineCore/GameEngineActor.h>


class IntroBackGround : public GameEngineActor
{
public:
	
	IntroBackGround();
	~IntroBackGround();

	
	IntroBackGround(const IntroBackGround& _Other) = delete;
	IntroBackGround(IntroBackGround&& _Other) noexcept = delete;
	IntroBackGround& operator=(const IntroBackGround& _Other) = delete;
	IntroBackGround& operator=(IntroBackGround&& _Other) noexcept = delete;



protected:

private:

	class GameEngineRenderer* Renderer;


	void Start() override;
};

