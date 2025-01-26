#pragma once

struct GLFWwindow;

class Renderer
{
public:
	Renderer(GLFWwindow* nativeWindow);
	~Renderer();

	void clear() const;
	void render() const;
	void beginImguiFrame() const;
	void endImguiFrame() const;
private:
	void setupOpenGL();
	void setupImgui(GLFWwindow* window);
};

