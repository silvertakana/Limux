#include "Limux.h"
#include "Limux/Core/EntryPoint.h"
#include "EditorLayer.h"

namespace LMX
{
	class LimuxEditor : public Application
	{
	public:
		LimuxEditor()
			: Application("Limux Editor")
		{
			PushLayer(new EditorLayer());
		}

		~LimuxEditor()
		{}
	};

	Application* CreateApplication()
	{
		return new LimuxEditor();
	}
}