#pragma once
#include "Objects/MeshRenderer.h"
#include "Objects/Material.h"

namespace ActaEngine
{
	class Box : public MeshRenderer
	{
	public:
		Box(Material* material);
	};
}