#include "lmxpch.h"

#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"

namespace LMX
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{}


	UUID Entity::GetUUID() const
	{
		return (HasComponent<IDComponent>() ? GetComponent<IDComponent>().ID : UUID{(uint64_t)-1});
	}

	std::string Entity::GetName() const
	{
		return (HasComponent<TagComponent>() ? GetComponent<TagComponent>().Tag : "");
	}
}
