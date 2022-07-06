#include "lmxpch.h"
#include "Entity.h"
#include "Scene.h"
#include "Components/Components.h"

namespace LMX
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}

	template<typename... Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		([&]()
			{
				auto view = src.view<Component>();
				for (auto srcEntity : view)
				{
					entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).ID);

					auto& srcComponent = src.get<Component>(srcEntity);
					dst.emplace_or_replace<Component>(dstEntity, srcComponent);
				}
			}(), ...);
	}
	
	template<typename... Component>
	static void CopyComponent(ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		CopyComponent<Component...>(dst, src, enttMap);
	}

	template<typename... Component>
	static void CopyComponentIfExists(Entity dst, Entity src)
	{
		([&]()
			{
				if (src.HasComponent<Component>())
					dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
			}(), ...);
	}

	template<typename... Component>
	static void CopyComponentIfExists(ComponentGroup<Component...>, Entity dst, Entity src)
	{
		CopyComponentIfExists<Component...>(dst, src);
	}

	Ref<Scene> Scene::Copy(Ref<Scene> other)
	{
		Ref<Scene> newScene = CreateRef<Scene>();

		newScene->m_ViewportWidth = other->m_ViewportWidth;
		newScene->m_ViewportHeight = other->m_ViewportHeight;

		auto& srcSceneRegistry = other->m_Registry;
		auto& dstSceneRegistry = newScene->m_Registry;
		std::unordered_map<UUID, entt::entity> enttMap;

		// Create entities in new scene
		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto e : idView)
		{
			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
			Entity newEntity = newScene->CreateEntityWithUUID(uuid);
			enttMap[uuid] = (entt::entity)newEntity;
		}

		// Copy components (except IDComponent)
		CopyComponent(AllComponents {}, dstSceneRegistry, srcSceneRegistry, enttMap);

		return newScene;
	}

	Entity Scene::CreateEntity()
	{
		return CreateEntityWithUUID(UUID());
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid)
	{
		Entity entity = Entity(m_Registry.create(), m_Registry);
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		
	}
	void Scene::OnRender(Ref<Shader> shader)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<MeshesComponent>);
		for (auto& entity : group)
		{
			auto [transform, meshes] = group.get<TransformComponent, MeshesComponent>(entity);
			meshes.Draw(shader, transform.GetTransform());
		}
	}
}