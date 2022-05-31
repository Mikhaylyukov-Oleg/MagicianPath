#include "Engine.h"
#include "TextureManager.h"
#include "SDL_image.h"
#include "Transform.h"
#include "Magician.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

Engine* Engine::s_Instance = nullptr;
Magician* player = nullptr;

bool Engine::Init()
{
	if ((SDL_Init(SDL_INIT_VIDEO) != 0) && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("SavingThePrincess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	MapParser::GetInstance()->Load();
	m_LevelMap = MapParser::GetInstance()->GetMap("level1");

	TextureManager::GetInstance()->Load("player_idle", "Assets/idle.png");
	TextureManager::GetInstance()->Load("player_run", "Assets/run.png");
	TextureManager::GetInstance()->Load("bg", "Assets/Images/bg.png");

	player = new Magician(new Properties("player_idle", 240, 368, 97, 88));
	
	Camera::GetInstance()->SetTarget(player->GetOrigin());

	return m_IsRunning = true; 
}

void Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
}

void Engine::Quit()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	player->Update(dt);
	Camera::GetInstance()->Update();
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 1920, 1080);
	m_LevelMap->Render();

	player->Draw();
	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();

}