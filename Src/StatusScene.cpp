/**
*@file StatusScene.cpp
*/

#include "StatusScene.h"
#include "GLFWEW.h"

/**
*プレイヤーの入力を処理する
*/

void StatusScene::ProcessInput() 
{
	GLFWEW::Window& window = GLFWEW::Window::Intance();
	if (window.GetGamePad().buttonDown & GamePad::START)
	{
		SceneStack::Instance().Pop();
	}
}