#pragma once
#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
#include "ImGui/ImGui_Main.h"
#endif
namespace ActaEngine
{
	class OpenGLRenderer
	{
	public:
		OpenGLRenderer(GLFWwindow* window);
		~OpenGLRenderer();

	public:
		void Draw();
		void Wireframe();
		void ImGuiRender(std::function<void()> EditorUpdate);

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
	public:
		ImGui_Main imgui;
		std::function<void()> OnEditorUpdate;
#endif

	private:
		bool wireframe;

	};
}