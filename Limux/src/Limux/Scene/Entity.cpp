#include "lmxpch.h"

#include "Entity.h"
#include "Components/Components.h"


LMX::Entity::Entity(entt::entity handle, Scene* scene)
	: m_EntityHandle(handle), m_Scene(scene)
{}


LMX::UUID LMX::Entity::GetUUID() const
{
	return GetComponent<IDComponent>().ID;
}

const std::string& LMX::Entity::GetName() const
{
	return GetComponent<TagComponent>().Tag;
}
