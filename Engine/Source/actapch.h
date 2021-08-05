#pragma once

#include <vector>
#include <functional>
#include <stack>

#include "spdlog/spdlog.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
#include "imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

	#define UNIT_TESTING false
		#if UNIT_TESTING
		#define CATCH_CONFIG_MAIN
		#include "catch.hpp"
	#endif
#endif