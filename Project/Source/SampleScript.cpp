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

	void Start() override
	{

	}

	//TODO: not updating yet
	void Update() override
	{
		Application::Update();
	}
};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}