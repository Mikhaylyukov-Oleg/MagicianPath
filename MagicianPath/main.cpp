#include "Engine.h"


int main(int argc, char* argv[])
{	
	Engine* enginePtr = Engine::GetInstance();
	enginePtr->Init();
	while (enginePtr->IsRunning())
	{
		enginePtr->Events();
		enginePtr->Update();
		enginePtr->Render();
	}
	enginePtr->Clean();
	return 0;
}