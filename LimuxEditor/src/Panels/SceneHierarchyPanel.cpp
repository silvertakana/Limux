#include <imgui/imgui.h>

#include "Limux.h"
#include "Limux/Scene/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>
#include "SceneHierarchyPanel.h"

namespace LMX
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		auto& nodeCom = m_Context->m_RootNode->GetComponent<NodeComponent>();
		//nodeCom.RemoveDestroyedChildren();
		auto& children = nodeCom.Children;
		for (auto& i : children)
		{
			DrawEntityNode({ i, m_Context.get() });
		}
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};
		ImGui::End();
		
		
		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string tag = "Unamed";
		if(entity.HasComponent<TagComponent>()) tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			if (entity.HasComponent<NodeComponent>())
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
				auto& nodeCom = entity.GetComponent<NodeComponent>();
				//nodeCom.RemoveDestroyedChildren();
				auto& children = nodeCom.Children;
				for (auto& i : children)
				{
					DrawEntityNode({ i, m_Context.get() });
				}
			}
			ImGui::TreePop();
		}

	}
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		
		if (entity.HasComponent<IDComponent>())
		{
			auto& uuid = entity.GetComponent<IDComponent>().ID;
			ImGui::Text("UUID: %d", uuid);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transformCom = entity.GetComponent<TransformComponent>();
				auto& transform = transformCom.Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
				auto eulerRotation = glm::eulerAngles(transformCom.GetRotation());
				ImGui::DragFloat3("Rotation", &eulerRotation[0], 0.1f);
				transformCom.SetRotation(eulerRotation);
				auto scale = transformCom.GetScale();
				ImGui::DragFloat3("Scale", &scale[0], 0.1f);
				transformCom.SetScale(scale);

				ImGui::TreePop();
			}
		}
	}
}