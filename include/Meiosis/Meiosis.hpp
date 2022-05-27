#pragma once

#include "Core/Core.hpp"


// ---- Core
#include "Core/Application.hpp"
// #include "Core/Core.hpp" ---- above
#include "Core/Entrypoint.hpp"
#include "Core/GraphicsContext.hpp"
#include "Core/Input.hpp"
#include "Core/KeyCodes.hpp"
#include "Core/Log.hpp"
#include "Core/LogHelper.hpp"
#include "Core/MouseCodes.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"

// ---- Events
#include "Events/ApplicationEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

// ---- imgui
#include "imgui/ImguiLayer.hpp"

// ---- Layer
#include "Layer/Layer.hpp"
#include "Layer/LayerStack.hpp"

// ---- Renderer ----
#include "Renderer/Camera.hpp"
#include "Renderer/Camera2D.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/RendererBuffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"

// ---- Scene ----
#include "Scene/Components.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Scene.hpp"
#include "Scene/SceneCamera.hpp"

// ---- Util
#include "Util/FileUtils.hpp"
#include "Util/Random.hpp"