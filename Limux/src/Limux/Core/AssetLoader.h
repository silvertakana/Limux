#pragma once
#include "Limux/Core/Base.h"

namespace LMX
{
	namespace AssetLoader
	{
		LMX::Ref<std::vector<char>> LoadBuffer(const std::string& path);
		std::string LoadFile(const std::string& path);
	}
}