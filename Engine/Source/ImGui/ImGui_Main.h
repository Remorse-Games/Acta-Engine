#pragma once

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)

class ImGui_Main
{
public:
	void Init(GLFWwindow* window);
	void Render(std::function<void()> f);
	void Destroy();
};

#endif