/**
*@file MainGameScene.cpp
*/

#include "MainGameScene.h"
#include "StatusScene.h"
#include "GameOverScene.h"
#include "GLFWEW.h"

/**
*ƒvƒŒƒCƒ„[‚Ì“ü—Í‚ğˆ—‚·‚é
*/

void MainGameScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Intance();
	if (window.GetGamePad().buttonDown & GamePad::START)
	{
		if (!flag)
		{
			flag = true;
			SceneStack::Instance().Push(std::make_shared<StatusScene>());
		}
		else
		{
			SceneStack::Instance().Replace(std::make_shared<GameOverScene>());
		}
	}
}