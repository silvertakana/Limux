#pragma once
#include "Limux/Core/Timestep.h"
#include "Limux/Renderer/Shader.h"

namespace LMX
{
	class Entity;
	
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
	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		
		entt::registry m_Registry;
	};
}

