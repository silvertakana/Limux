#pragma once

#include "Limux/Core/DefConfig.h"
// For use in Limux application
// ---Debug---------------------------
#include "Limux/Debug/Instrumentor.h"

#include "Limux/Core/Application.h"
#include "Limux/Core/Layer.h"
#include "Limux/Core/Log.h"
#include "Limux/ImGui/ImGuiLayer.h"
#include "imgui.h"

#include "Limux/Core/Input.h"
#include "Limux/Core/KeyCodes.h"
#include "Limux/Core/MouseCodes.h"

#include "Limux/Core/Timestep.h"

// ---Renderer------------------------
#include "Limux/Renderer/Renderer.h"
#include "Limux/Renderer/RenderCommand.h"

#include "Limux/Renderer/Vertex.h"
#include "Limux/Renderer/Buffer.h"
#include "Limux/Renderer/Framebuffer.h"
#include "Limux/Renderer/Shader.h"
#include "Limux/Renderer/Texture.h"
#include "Limux/Renderer/VertexArray.h"
#include "Limux/Renderer/Mesh.h"
#include "Limux/Renderer/SceneNode.h"

#include "Limux/Scene/Entity.h"
#include "Limux/Scene/Scene.h"
#include "Limux/Scene/Components/Components.h"