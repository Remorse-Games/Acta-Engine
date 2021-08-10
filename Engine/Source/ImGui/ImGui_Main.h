#pragma once

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)

class ImGui_Main
{
public:
	void Init(GLFWwindow* window);
	void Destroy();
};

#endif