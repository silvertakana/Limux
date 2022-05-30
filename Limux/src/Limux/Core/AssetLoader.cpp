#include "lmxpch.h"
#include "AssetLoader.h"
namespace LMX
{
    namespace AssetLoader
    {
        LMX::Ref<std::vector<char>> LoadBuffer(const std::string& path)
        {
            LMX_PROFILE_FUNCTION();
            std::ifstream file("samplefile.bin", std::ios::binary);
            auto mem = new std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
            return LMX::Ref<std::vector<char>>{ mem };
        }

        std::string LoadFile(const std::string& path)
        {
            LMX_PROFILE_FUNCTION();
            std::ifstream t(path);
            LMX_ASSERT(t.is_open(), "Can't open file {0}", path);
            return { (std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>() };
        }
    }
	
}
