#include <Core/Application.h>
#include <imgui/imgui.h>

Application::Application()
	: m_window{ nullptr }, m_renderer{ nullptr } {}

Application::~Application() {}

bool Application::initialize()
{
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
	while (!m_window->shouldClose())
	{
		m_window->pollEvents();

		// Start ImGui frame
		m_renderer->beginImguiFrame();

		// ImGui UI elements
		ImGui::ShowDemoWindow();
		
		m_renderer->clear();
		m_renderer->render();

		// End ImGui frame
		m_renderer->endImguiFrame();

		m_window->swapBuffers();
	}
}

void Application::shutdown()
{
	delete m_window;
	delete m_renderer;
}
