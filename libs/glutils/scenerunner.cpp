#include "scenerunner.h"

#include "glutils.h"

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

SceneRunner::SceneRunner(const std::string& windowTitle, int width, int height, int samples) : debug(true) {
	// Initialize GLFW
	if (!glfwInit()) 
		exit(EXIT_FAILURE);

#ifdef __APPLE__
	// Select OpenGL 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
	// Select OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	if (debug)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	if (samples > 0)
		glfwWindowHint(GLFW_SAMPLES, samples);

	// Open the window
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, windowTitle.c_str(), NULL, NULL);
	if (!window) {
		std::cerr << "Unable to create OpenGL context." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	// Get framebuffer size
	glfwGetFramebufferSize(window, &fbw, &fbh);

	// Load the OpenGL functions.
	if (!gladLoadGL())
	{
		std::cerr << "Unable to load GL functions." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
		
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifndef __APPLE__
	ImGui_ImplOpenGL3_Init("#version 430 core");
#else
	ImGui_ImplOpenGL3_Init("#version 410 core");
#endif
	ImGui::StyleColorsDark();

	GLUtils::dumpGLInfo();

	// Initialization
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
#ifndef __APPLE__
	if (debug) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLUtils::debugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, nullptr, GL_FALSE);
	}
#endif
}

int SceneRunner::run(std::unique_ptr<Scene> scene) {
	// Enter the main loop
	mainLoop(window, std::move(scene));

#ifndef __APPLE__
	if (debug)
		glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
			GL_DEBUG_SEVERITY_NOTIFICATION, -1, "End debug");
#endif

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	return EXIT_SUCCESS;
}

void SceneRunner::mainLoop(GLFWwindow* window, std::unique_ptr<Scene> scene) {
	scene->setDimensions(fbw, fbh);
	scene->initScene();
	scene->resize(fbw, fbh);

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		GLUtils::checkForOpenGLError(__FILE__, __LINE__);

		scene->update(float(glfwGetTime()));
		scene->render();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("GUI");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwPollEvents();
		int state = glfwGetKey(window, GLFW_KEY_SPACE);
		if (state == GLFW_PRESS)
			scene->animate(!scene->animating());

		glfwSwapBuffers(window);
	}
}
