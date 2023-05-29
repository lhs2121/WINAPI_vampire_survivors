#pragma once
#include <GameEngineCore/GameEngineActor.h>


class Image : public GameEngineActor
{
public:
	
	Image();
	~Image();

	
	Image(const Image& _Other) = delete;
	Image(Image&& _Other) noexcept = delete;
	Image& operator=(const Image& _Other) = delete;
	Image& operator=(Image&& _Other) noexcept = delete;



protected:

private:

	class GameEngineRenderer* Renderer;


	void Start() override;
};

