#include "Engine.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
	Engine* enginePtr = Engine::GetInstance();
	enginePtr->Init();
	while (enginePtr->IsRunning())
	{
		enginePtr->Events();
		enginePtr->Update();
		enginePtr->Render();
		Timer::GetInstance()->Tick();
	}
	enginePtr->Clean();
	return 0;
}