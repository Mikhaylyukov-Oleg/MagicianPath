#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"

#define SCREEN_WIDTH 600
#define SCREEN_HAIGTH 600

class Engine
{
public :
	static Engine* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();		
	}

	bool Init();
	void Clean();
	void Quit();

	void Update();
	void Render();
	void Events();
	
	inline bool IsRunning()
	{
		return m_IsRunning;
	}

	inline SDL_Renderer* GetRenderer()
	{
		return m_Renderer;
	}

private:
	Engine(){}
	bool m_IsRunning = false;
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
	static Engine* s_Instance;
};

#endif ENGINE_H