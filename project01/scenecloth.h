#pragma once

#include "scene.h"
#include "glslprogram.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class SceneCloth : public Scene
{
public:
	SceneCloth();

	void initScene() override;
	void update(float t) override;
	void render() override;
	void resize(int, int) override;
	void uiUpdate() override;

private:
	void compileAndLinkShader();
	void initBuffers();
	void setMatrices();

private:
	GLSLProgram renderProg, computeProg, computeProgNorm;

	GLuint clothVao;
	GLuint numElements;

	glm::ivec2 nParticles;  // Number of particles in each dimension
	glm::vec2 clothSize;    // Size of cloth in x and y

	float time, deltaT, speed;
	GLuint readBuf;
	GLuint posBufs[2], velBufs[2];
	GLuint normBuf, elBuf, tcBuf;
	bool wireframe;
};
