#include "Core/Application.h"
#include "Core/Window.h"
#include "Rendering/Renderer.h"
#include "Utils/Logger.h"

#include <imgui/imgui.h>

//#define SHOW_DEMO_UI
#define SHOW_METRICS_UI

Application::Application()
	: m_logger{ Logger::getInstance() }
	, m_window{ nullptr }
	, m_renderer{ nullptr } {
}

Application::~Application() {}

bool Application::initialize()
{
	m_logger.log("Initializing application...", Logger::Level::Info);
	m_window = new Window("3D Model Renderer", 1280, 720);
	if (!m_window->initialize())
	{
		return false;
	}

	m_renderer = new Renderer(m_window->getNativeWindow());
	return true;
}

void Application::run()
{
	m_logger.log("Application is now RUNNING!", Logger::Level::Info);
	while (!m_window->shouldClose())
	{
		m_window->pollEvents();

		// Start ImGui frame
		m_renderer->beginImguiFrame();

#ifdef SHOW_DEMO_UI
		// ImGui Demor UI elements
		ImGui::ShowDemoWindow();
#endif

#ifdef SHOW_METRICS_UI
		// Show metrics
		showMetrics();
#endif

		m_renderer->clear();
		m_renderer->render();

		// End ImGui frame
		m_renderer->endImguiFrame();

		m_window->swapBuffers();
	}
}

void Application::shutdown()
{
	m_logger.log("Shutting down...", Logger::Level::Info);
	delete m_window;
	delete m_renderer;
}

void Application::showMetrics() const
{
	// Metrics
	ImGuiWindowFlags metrics_window_flags = 0;
	metrics_window_flags |= ImGuiWindowFlags_NoTitleBar;
	metrics_window_flags |= ImGuiWindowFlags_NoBackground;
	metrics_window_flags |= ImGuiWindowFlags_NoMove;
	metrics_window_flags |= ImGuiWindowFlags_NoDecoration;
	metrics_window_flags |= ImGuiWindowFlags_NoMouseInputs;
	ImGui::Begin("Metrics", (bool*)0, metrics_window_flags);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)"
		, 1000.0f / ImGui::GetIO().Framerate
		, ImGui::GetIO().Framerate);
	ImGui::Text("%d vertices, %d indices (%d triangles)"
		, ImGui::GetIO().MetricsRenderVertices
		, ImGui::GetIO().MetricsRenderIndices
		, ImGui::GetIO().MetricsRenderIndices / 3);
	ImGui::End();
}
