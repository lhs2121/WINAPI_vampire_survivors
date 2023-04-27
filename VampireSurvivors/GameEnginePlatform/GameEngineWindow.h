#pragma once
#include <Windows.h>
#include <string>

// 설명 :
class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance); //객체로 접근해서 윈도우를 만들기위한 함수

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)()); //이벤트 핸들러

protected:

private:
	static HINSTANCE Instance; // 프로그램 핸들
	std::string Title = ""; // 윈도우 형식 타이틀
	HWND hWnd = nullptr; // 윈도우창 핸들

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //콜백함수
	void InitInstance();
	void MyRegisterClass();
};

