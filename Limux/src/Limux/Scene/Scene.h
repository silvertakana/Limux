#pragma once
#include "Limux/Core/Timestep.h"
#include "Limux/Renderer/Shader.h"

namespace LMX
{
	class Entity;
	class EditorLayer;
	
	class Scene
	{
	public:
		Scene();
		~Scene();
		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity();
		Entity CreateEntityWithUUID(UUID uuid);
		void DestroyEntity(Entity entity);

		const entt::registry& GetReg() const { return m_Registry; }
		entt::registry& GetReg() { return m_Registry; }

		void OnUpdate(Timestep ts);
		void OnRender(Ref<Shader> shader);
		void OnViewportResize(uint32_t width, uint32_t height);
	protected:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		
		Entity* m_ActiveCamera = nullptr;
		
		entt::registry m_Registry;
		friend EditorLayer;
	};
}

