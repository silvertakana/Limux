#pragma once
namespace LMX
{
	enum class DataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	static uint32_t ShaderDataTypeSize(DataType type)
	{
		switch (type)
		{
		case DataType::Float:    return 4;
		case DataType::Float2:   return 4 * 2;
		case DataType::Float3:   return 4 * 3;
		case DataType::Float4:   return 4 * 4;
		case DataType::Mat3:     return 4 * 3 * 3;
		case DataType::Mat4:     return 4 * 4 * 4;
		case DataType::Int:      return 4;
		case DataType::Int2:     return 4 * 2;
		case DataType::Int3:     return 4 * 3;
		case DataType::Int4:     return 4 * 4;
		case DataType::Bool:     return 1;
		}

		LMX_ASSERT(false, "Unknown DataType!");
		return 0;
	}
	static uint32_t GetComponentCount(DataType type)
	{
		switch (type)
		{
		case DataType::Float:   return 1;
		case DataType::Float2:  return 2;
		case DataType::Float3:  return 3;
		case DataType::Float4:  return 4;
		case DataType::Mat3:    return 3 * 3;
		case DataType::Mat4:    return 4 * 4;
		case DataType::Int:     return 1;
		case DataType::Int2:    return 2;
		case DataType::Int3:    return 3;
		case DataType::Int4:    return 4;
		case DataType::Bool:    return 1;
		}

		LMX_ASSERT(false, "Unknown DataType!");
		return 0;
	}
}