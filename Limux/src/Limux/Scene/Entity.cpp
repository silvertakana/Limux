#include "lmxpch.h"

#include "Entity.h"
#include "Components/Components.h"


LMX::Entity::Entity(entt::entity handle, Scene& scene)
	: m_EntityHandle(handle), m_Registry(&scene.GetReg())
{}

LMX::Entity::Entity(entt::entity handle, entt::registry & registry)
	: m_EntityHandle(handle), m_Registry(&registry)
{}


LMX::UUID LMX::Entity::GetUUID()
{
	return GetComponent<IDComponent>().ID;
}

const std::string& LMX::Entity::GetName()
{
	return GetComponent<TagComponent>().Tag;
}
