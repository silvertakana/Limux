#pragma once
#include "Limux/Core/Timestep.h"
#include "Limux/Renderer/Shader.h"
#include "entt.hpp"

namespace LMX
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();
		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& tag = "");
		Entity CreateEntityWithUUID(UUID uuid, const std::string& tag = "");
		void DestroyEntity(Entity entity);

		const entt::registry& GetReg() const { return m_Registry; }
		entt::registry& GetReg() { return m_Registry; }

		void OnUpdate(Timestep ts);
		void OnRender(Ref<Shader> shader);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	protected:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		
		entt::entity m_ActiveCamera;
		Ref<Entity> m_RootNode;
		
		entt::registry m_Registry;
		
		friend Entity;
		friend class EditorLayer;
		friend class SceneHierarchyPanel;
		friend class NodeComponent;
	};
}

