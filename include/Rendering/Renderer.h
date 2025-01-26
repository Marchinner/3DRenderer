#pragma once

struct GLFWwindow;
struct ImGuiIO;

class Renderer
{
public:
	Renderer(GLFWwindow* nativeWindow);
	~Renderer();

	void clear() const;
	void render() const;
	void beginImguiFrame() const;
	void endImguiFrame() const;
	ImGuiIO& getImguiIo() const;
private:
	void setupOpenGL();
	void setupImgui(GLFWwindow* window);
};

