#include "lmxpch.h"

#include "LoadFiles.h"
#include "Lumix/Log.h"

namespace LMX
{
	std::pair<std::string, std::string> loadShader(const char* path)
	{
		std::ifstream file(path);
		LMX_ASSERT(!file.is_open(), "Unable to open shader file: {0}", path);
		std::string line, shader[2];
		enum Mode
		{
			NONE = -1,
			VERTEX, FRAGMENT
		};
		Mode mode = NONE;
		while (std::getline(file, line))
		{
			if (line.contains("#shader"))
				if (line.contains("vertex"))
					mode = VERTEX;
				else if (line.contains("fragment"))
					mode = FRAGMENT;
				else
					mode = NONE;
			else if (mode != NONE)
				shader[mode] += line + '\n';
		}
		return { shader[VERTEX], shader[FRAGMENT] };
	}
	std::string loadFile(const char* path)
	{
		std::ifstream file(path);
		LMX_ASSERT(!file.is_open(), "Unable to open file: {0}", path);
		return { (std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()) };
	}
}