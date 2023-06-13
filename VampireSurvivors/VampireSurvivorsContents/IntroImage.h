#pragma once
#include <GameEngineCore/GameEngineActor.h>

class IntroImage : public GameEngineActor
{
public:
	
	IntroImage()
	{

	}
	~IntroImage()
	{

	}

	
	IntroImage(const IntroImage& _Other) = delete;
	IntroImage(IntroImage&& _Other) noexcept = delete;
	IntroImage& operator=(const IntroImage& _Other) = delete;
	IntroImage& operator=(IntroImage&& _Other) noexcept = delete;



protected:

private:
	class GameEngineRenderer* Renderer;
	void Start() override;
};

