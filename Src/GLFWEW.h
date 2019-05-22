/*
*@file GLFWEW.h
*/

#ifndef GLFWEW_H_INCLUDED
#define GLFWEW_H_INCLUDED
#include <GL/glew.h>
#include "GamePad.h"
#include <GLFW/glfw3.h>

namespace GLFWEW {

	/*
	*GLFWとGLEWのラッパークラス
	*/
	
	class Window
	{
	public:
		static Window& Intance();
		bool Init(int w, int h, const char* title);
		bool ShoudClose() const;
		void SwapBuffers() const;

		void InitTimer();
		void UpdateTimer();
		double DeltaTime() const;
	
		bool IsKeyPressed(int key) const;
		const GamePad& GetGamePad() const;

	private:
		Window() = default;	//デフォルトコンストラクタ(変数が作成されるとき)
		~Window();	//デストラクタ(変数が削除されるとき)
		Window(const Window&) = delete;	//コピーコンストラクタ(変数を初期化するとき)
		Window& operator = (const Window&) = delete;	//コピー代入演算子
		void UpdateGamePad();

		bool isGLFWInitialized = false;
		bool isInitialized = false;
		GLFWwindow* window = nullptr;
		double previousTime = 0;
		double deltaTime = 0;
		GamePad gamepad;

	};

}	// namespace GLFWEW

#endif // !GLFWEW_H_INCLUDED
