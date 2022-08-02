#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "entt.hpp"
#include "Limux/Scene/Scene.h"

namespace LMX
{
	struct NodeComponent
	{
		std::vector<entt::entity> Children;
		NodeComponent(Scene* scene) :m_Scene(scene) {};
		NodeComponent() = default;
		NodeComponent(const NodeComponent& other) :Children(other.Children), m_Scene(other.m_Scene) {};
		NodeComponent(Scene* scene, const std::vector<entt::entity>& children)
			: Children(children), m_Scene(scene)
		{}
		void RemoveDestroyedChildren();
		void AddChild(entt::entity child);
		void RemoveChild(size_t index);
		void RemoveChild(entt::entity child);
		void AddModel(const std::string& path);

		virtual size_t size() const { return Children.size(); }
	protected:
		Scene* m_Scene = nullptr;
	};
}