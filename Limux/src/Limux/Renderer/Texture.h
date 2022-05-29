#pragma once
#include "Limux/Core/Core.h"
namespace LMX
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		enum Settings
		{
			MinLinear = BIT(0),
			MagLinear = BIT(1),
			Clamp = BIT(2),
			Mirror = BIT(3),
			Mipmap = BIT(4),
			Red = BIT(5),
			RGB = BIT(6),
		};
		
		static Ref<Texture2D> Load(const std::string& path, int setting);
	};
}

