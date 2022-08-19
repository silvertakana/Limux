#include <imgui/imgui.h>

#include "Limux.h"
#include "Limux/Scene/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

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

		// Right-click on blank space
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}
		
		ImGui::End();
		
		
		ImGui::Begin("Properties");
		if (m_SelectionContext) {
			DrawComponents(m_SelectionContext);
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");
			
			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>().SetupPerspective(glm::radians(80.f), 1920, 1080, 0.1f, 1000.0f);
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Light"))
				{
					m_SelectionContext.AddComponent<LightComponent>(LightComponent::LightType::Point, glm::vec3{ 0.5 });
					ImGui::CloseCurrentPopup();
				}
				
				if (ImGui::MenuItem("Node"))
				{
					m_SelectionContext.AddComponent<NodeComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string tag = "Unnamed";
		if(entity.HasComponent<TagComponent>()) tag = entity.GetComponent<TagComponent>().Tag; // gets tag component if exists

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			if (entity.HasComponent<NodeComponent>())
			{
				auto& nodeCom = entity.GetComponent<NodeComponent>();
				nodeCom.RemoveDestroyedChildren();
				auto& children = nodeCom.Children;
				for (auto& i : children)
				{
					DrawEntityNode({ i, m_Context.get() });
				}
			}
			ImGui::TreePop();
		}

	}
	bool isPathExist(const std::string& s)
	{
		struct stat buffer;
		return (stat (s.c_str(), &buffer) == 0);
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		static entt::entity prevEnttEntity;
		
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
		static glm::vec3 eulerRotation;
		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transformCom = entity.GetComponent<TransformComponent>();
				auto& transform = transformCom.Transform;
				DrawVec3Control("Position", *(glm::vec3*)&transform[3]);

				if (entity.GetEnttEntity() != prevEnttEntity ||
					glm::quat(glm::radians(eulerRotation)) != transformCom.GetRotation())
				{
					eulerRotation = glm::degrees(glm::eulerAngles(transformCom.GetRotation()));
				}
				DrawVec3Control("Rotation", eulerRotation);
				
				transformCom.SetRotation(glm::radians(eulerRotation));
				auto scale = transformCom.GetScale();
				DrawVec3Control("Scale", scale);
				
				transformCom.SetScale(scale);

				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<MeshesComponent>()) {
			if (ImGui::TreeNodeEx((void*)typeid(MeshesComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Meshes"))
			{
				auto& meshesCom = entity.GetComponent<MeshesComponent>();
				auto& meshes = meshesCom.Meshes;
				size_t verticesCount;
				size_t indicesCount;
				for (auto& mesh : meshes)
				{
					verticesCount = mesh->vertices.size();
					indicesCount  = mesh->indices.size();
					ImGui::Text("Mesh: %d vertices, %d indices, %d triangles", verticesCount, indicesCount, indicesCount/3);
				}
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<NodeComponent>()) {
			if (ImGui::TreeNodeEx((void*)typeid(NodeComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Node"))
			{
				auto& nodeCom = entity.GetComponent<NodeComponent>();
				auto& children = nodeCom.Children;
				ImGui::Text("Children Count %d", children.size());
				if (ImGui::Button("Add Child"))
					nodeCom.AddChild(m_Context->CreateEntity("Empty Entity"));
				
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<TexturesComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TexturesComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Textures"))
			{
				auto& texturesCom = entity.GetComponent<TexturesComponent>();
				auto& textures = texturesCom.Textures;
				for (auto& i : textures)
				{
					auto& texture2D = *(Texture2D*)i.get();
					if (ImGui::TreeNodeEx((void*)typeid(TexturesComponent).hash_code(), ImGuiTreeNodeFlags_None, texture2D.GetPath().c_str()))
					{
						char buffer[256];
						memset(buffer, 0, sizeof(buffer));
						strcpy_s(buffer, sizeof(buffer), texture2D.GetPath().c_str());
						if (ImGui::InputText("Path", buffer, sizeof(buffer)))
						{
							texture2D.GetPath() = std::string(buffer);
						}
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<LightComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(LightComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Light"))
			{
				auto& lightCom = entity.GetComponent<LightComponent>();
				ImGui::Checkbox		("Enabled"	, &lightCom.Enabled	 );
				ImGui::ColorPicker3	("Color"	, &lightCom.Color[0] );
				ImGui::DragFloat	("Intensity", &lightCom.Intensity, 0.01f);

				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				bool isPrimary = m_Context->m_ActiveCamera == entity.GetEnttEntity();
				ImGui::Checkbox("Primary", &isPrimary);
				if(isPrimary) m_Context->m_ActiveCamera = entity.GetEnttEntity();
				ImGui::TreePop();
			}
		}
		//static char pathBuffer[256];
		//static bool isFounded = false;
		//ImGui::InputText("Directory", pathBuffer, sizeof(pathBuffer));
		//if (ImGui::Button("Load"))
		//{
		//	if (IsPathExist(pathBuffer))
		//		isFounded = true;
		//	else
		//		isFounded = false;
		//}
		//
		//if(isFounded)
		//	ImGui::Text("path exists");
		//else
		//	ImGui::Text("path does not exist");
		prevEnttEntity = entity.GetEnttEntity();
	}
}