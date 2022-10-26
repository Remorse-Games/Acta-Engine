#pragma once

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)

class ImGui_Main
{
public:
	ImGui_Main(GLFWwindow* window);
	~ImGui_Main();
};

#endif