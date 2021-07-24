#include "ActaEngine.h"

class Game : public Application
{
public:
	Game()
	{
		//spdlog::info("Start the game!");
	}

	~Game()
	{

	}
};

Application* CreateApplication()
{
	return new Game();
}