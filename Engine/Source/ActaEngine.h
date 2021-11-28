#pragma once

#include <functional>

//Core System
#include "Core/Application.h"
#include "System/Time.h"

//Events
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

//ImGui
#include "imgui.h"

//Objects
#include "Objects/Camera/Camera.h"
#include "Objects/MeshRenderer.h"
#include "Objects/Transform.h"
#include "Objects/Material.h"

//Primitives
#include "Objects/Primitives/Box.h"

//Renderer
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLWindow.h"

//Entry Point
#include "EntryPoint.h"
