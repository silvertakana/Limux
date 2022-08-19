 #include "EditorLayer.h"


namespace LMX
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{}

	void EditorLayer::OnAttach()
	{
		LMX_PROFILE_FUNCTION();
		
		LMX::Texture2D::SetDefaultTexture("res/textures/missing_texture.png");

		m_ActiveScene = CreateRef<Scene>();
		
		m_Camera = m_ActiveScene->CreateEntity();
		m_Camera.AddOrReplaceComponent<TagComponent>("Camera");
		m_Camera.AddOrReplaceComponent<CameraComponent>().SetupPerspective(glm::radians(80.f), 1920, 1080, 0.1f, 1000.0f);
		m_Camera.AddOrReplaceComponent<TransformComponent>(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 5.f, 5.f)));
		m_ActiveScene->m_ActiveCamera = m_Camera;
		
		m_Camera2 = m_ActiveScene->CreateEntity();
		m_Camera2.AddOrReplaceComponent<TagComponent>("Camera2");
		m_Camera2.AddOrReplaceComponent<CameraComponent>().SetupPerspective(glm::radians(80.f), 1920, 1080, 0.1f, 1000.0f);
		m_Camera2.AddOrReplaceComponent<TransformComponent>(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 5.f, 5.f)));
		
		m_Model = m_ActiveScene->CreateEntity();
		m_Model.AddOrReplaceComponent<TagComponent>("Model");
		m_Model.AddOrReplaceComponent<NodeComponent>().AddModel("res/models/FireHydrant/FireHydrantMesh.obj");
		m_Model.GetComponent<TransformComponent>().SetScale(glm::vec3{ 5 });

		m_Floor = m_ActiveScene->CreateEntity();
		m_Floor.AddOrReplaceComponent<TagComponent>("Floor");
		m_Floor.GetComponent<TransformComponent>().SetScale(glm::vec3{ 10 });
		std::vector<Vertex> vertices {
			{{-1, 0,  1}, {0, 1, 0}, {0, 1}, {1, 1, 1, 1}},
			{{ 1, 0,  1}, {0, 1, 0}, {1, 1}, {1, 1, 1, 1}},
			{{ 1, 0, -1}, {0, 1, 0}, {1, 0}, {1, 1, 1, 1}},
			{{-1, 0, -1}, {0, 1, 0}, {0, 0}, {1, 1, 1, 1}},
		};
		std::vector<unsigned int> indices {
			0, 1, 2,
			2, 3, 0
		};
		std::vector<Ref<Texture>> textures {
			Texture2D::Load("res/textures/Checkerboard.png", Texture2D::TextureType::Diffuse),
			Texture2D::Load(glm::vec4{0.3f}, Texture2D::TextureType::Specular)
		};



		m_Floor.AddOrReplaceComponent<MeshesComponent>().AddMesh(vertices, indices);
		m_Floor.GetComponent<MeshesComponent>().InitAll();
		m_Floor.AddOrReplaceComponent<TexturesComponent>().AddTextures(textures);
		m_Floor.GetComponent<TexturesComponent>().InitAll();
		
		m_Light = m_ActiveScene->CreateEntity();
		m_Light.AddOrReplaceComponent<TagComponent>("Light");
		m_Light.AddOrReplaceComponent<LightComponent>(LightComponent::LightType::Point, glm::vec3 { 0.5, 0.4, 0.0 });
		m_Light.GetComponent<TransformComponent>().SetTranslation(glm::vec3 { 12, 10, 16 });


		m_Shader = Shader::Load("res/shaders/shaded.shader");

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		class CameraController : public ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{}

			virtual void OnDestroy() override
			{}

			virtual void OnUpdate(Timestep ts) override
			{
				auto& transformCom = GetComponent<TransformComponent>();

				float translationSpeed = 5.0f, rotationSpeed = 3.0f;
				glm::vec3 up, front, right;
				up = glm::vec3(0.0f, 1.0f, 0.0f);
				front = glm::normalize(transformCom.GetRotationMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 1.f));
				right = glm::normalize(glm::cross(front, up));
				
				if(Input::IsKeyPressed(Key::Up))
					transformCom.Rotate( right, rotationSpeed * (float)ts);
				if(Input::IsKeyPressed(Key::Down))
					transformCom.Rotate(-right, rotationSpeed * (float)ts);
				if(Input::IsKeyPressed(Key::Left))
					transformCom.Rotate( up   , rotationSpeed * (float)ts);
				if(Input::IsKeyPressed(Key::Right))
					transformCom.Rotate(-up   , rotationSpeed * (float)ts);
				
				if (Input::IsKeyPressed(Key::W))
					transformCom.Translate( front * translationSpeed * (float)ts);
				if (Input::IsKeyPressed(Key::S))
					transformCom.Translate(-front * translationSpeed * (float)ts);
				if (Input::IsKeyPressed(Key::A))
					transformCom.Translate(-right * translationSpeed * (float)ts);
				if (Input::IsKeyPressed(Key::D))
					transformCom.Translate( right * translationSpeed * (float)ts);
				if (Input::IsKeyPressed(Key::E))
					transformCom.Translate( up    * translationSpeed * (float)ts);
				if (Input::IsKeyPressed(Key::Q))
					transformCom.Translate(-up    * translationSpeed * (float)ts);
				
					
			}
		};

		Entity(m_ActiveScene->m_ActiveCamera, m_ActiveScene.get()).AddOrReplaceComponent<NativeScriptComponent>().Bind<CameraController>();

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}
	void EditorLayer::OnDetach()
	{
		LMX_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LMX_PROFILE_FUNCTION();
		
		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			Entity(m_ActiveScene->m_ActiveCamera, m_ActiveScene.get()).GetComponent<CameraComponent>().SetupPerspective(glm::radians(80.f), m_ViewportSize.x, m_ViewportSize.y, 0.1f, 1000.0f);
		
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		
		{
			LMX_PROFILE_SCOPE("Scene Update");
			m_ActiveScene->OnUpdate(ts);
			//m_Model.GetComponent<TransformComponent>().Transform = m_Camera.GetComponent<TransformComponent>().Transform;
		}
		
		{
			LMX_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}

		{
			LMX_PROFILE_SCOPE("Update");
		}
		{
			LMX_PROFILE_SCOPE("Renderer Draw");
			Renderer::BeginScene();
			m_ActiveScene->OnRender(m_Shader);
			Renderer::EndScene();
			m_Framebuffer->Unbind();
		}
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		LMX_PROFILE_FUNCTION();
		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSizeX;
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2 { m_ViewportSize.x, m_ViewportSize.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar(); 

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event & e, Timestep ts)
	{}

}