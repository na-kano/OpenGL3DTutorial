/**
*@file TitleScene.cpp
*/

#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"

/**
*プレイヤーの入力を処理する
*/

void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Intance();
	if (window.GetGamePad().buttonDown & GamePad::START)
	{
		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
	}
}