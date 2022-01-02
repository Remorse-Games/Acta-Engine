#pragma once
#include "Objects/MeshRenderer.h"
#include "Objects/Material.h"

namespace ActaEngine
{
	class Box : public MeshRenderer
	{
	public:
		Box(Material& material, const std::string& objectName);

	//private:
		std::string m_ObjectName;
	};
}