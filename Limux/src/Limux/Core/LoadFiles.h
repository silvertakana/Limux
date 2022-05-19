#pragma once

namespace LMX
{
	std::string loadFile(const std::string& path)
	{
		std::ifstream file(path);
		LMX_ASSERT(file.is_open(), "Unable to open file: {0}", path);
		return { (std::istreambuf_it
			erator<char>(file)),
			(std::istreambuf_iterator<char>()) };
	}
}