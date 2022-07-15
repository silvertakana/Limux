#pragma once
#include "entt.hpp"
#include "Limux/Core/Base.h"
#include "Scene.h"

namespace LMX
{
	class Entity
	{
		entt::entity m_EntityHandle {entt::null};
		Scene* m_Scene = nullptr;
	public:
		
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		virtual ~Entity() = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			LMX_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, m_Scene, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, m_Scene, std::forward<Args>(args)...);
			return component;
		}
		template<typename T>
		T& GetComponent() const
		{
			LMX_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename ...Components>
		bool HasComponent() const
		{
			LMX_ASSERT(m_Scene, "Entity is not yet initilized");
			return m_Scene->m_Registry.any_of<Components...>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			LMX_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		UUID GetUUID() const;
		const std::string& GetName() const;
		Scene& GetScene() const { return *m_Scene; }
		entt::registry& GetReg() const { return m_Scene->GetReg(); }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	};
}