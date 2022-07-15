#pragma once

#include "Limux/Core/Base.h"
#include "Limux/Core/Log.h"
#include "Limux/Scene/Scene.h"
#include "Limux/Scene/Entity.h"

namespace LMX
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}