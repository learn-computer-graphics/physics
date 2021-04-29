#pragma once

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include "scene.h"

#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

class SceneRunner {
public:
	SceneRunner(const std::string& windowTitle, int width = WIN_WIDTH, int height = WIN_HEIGHT, int samples = 0);
	int run(std::unique_ptr<Scene> scene);

private:
	void mainLoop(GLFWwindow* window, std::unique_ptr<Scene> scene);

private:
	GLFWwindow* window;
	int fbw;
	int fbh;
	bool debug;
};
