#include "lmxpch.h"
#include "Entity.h"
#include "Scene.h"
#include "Components/Components.h"

namespace LMX
{
	Scene::Scene()
	{
		m_Registry = {};
		m_RootNode = CreateRef<Entity>(m_Registry.create(), this);
		m_RootNode->AddComponent<IDComponent>(UUID());
		m_RootNode->AddComponent<TagComponent>("SceneRootNode");
		m_RootNode->AddComponent<NodeComponent>();
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
		Entity entity = Entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		m_RootNode->GetComponent<NodeComponent>().Children.push_back(entity);
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity { entity, this };

						nsc.Instance->OnCreate();
					}
					nsc.Instance->OnUpdate(ts);
				});
		}
	}
	void RenderEntity(const Entity& entity, Ref<Shader> shader, glm::mat4 offset)
	{
		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			offset = transform.Transform * offset;
			
			if(entity.HasComponent<MeshesComponent>())
			{
				auto& meshes = entity.GetComponent<MeshesComponent>();
				meshes.Draw(shader, offset);
			}
		}
		if (entity.HasComponent<NodeComponent>())
		{
			auto& node = entity.GetComponent<NodeComponent>();
			for (auto& child : node.Children)
			{
				RenderEntity({ child, &entity.GetScene() }, shader, offset);
			}
		}
	}
	void Scene::OnRender(Ref<Shader> shader)
	{
		shader->Bind();
		CameraComponent& cameraCom = m_ActiveCamera->GetComponent<CameraComponent>();
		TransformComponent& cameraTrans = m_ActiveCamera->GetComponent<TransformComponent>();

		shader->SetUniform("u_CamMatrix", cameraCom.GenCamMatrix(cameraTrans));
		
		RenderEntity(*m_RootNode, shader, glm::mat4{1.f});
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
	}
}