#include "ActaEngine.h"

class Game : public ActaEngine::Application
{
public:
	Game()
	{
		spdlog::info("Start the game!");
	}

	~Game()
	{

	}
};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}