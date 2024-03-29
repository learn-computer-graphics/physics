#include "scenecloth.h"
#include "texture.h"

#include <imgui/imgui.h>

#include <iostream>
using std::endl;
using std::cerr;

#include <vector>
using std::vector;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;

#define PRIM_RESTART 0xffffff

SceneCloth::SceneCloth()
	: clothVao(0), numElements(0),
	nParticles(40, 40), clothSize(4.0f, 3.0f),
	time(0.0f), deltaT(0.0f), speed(200.0f), readBuf(0),
	lightDir(glm::vec3(0)), lightColor(glm::vec3(1)),
	specularity(0.2f), ambiant(0.2f), diffuse(0.8f), shininess(80),
	wireframe(false), gravity(glm::vec3(0, -10, 0)),
	particleMass(0.1), springK(2000), wind(false),
	windStrength(0.5), windDir(glm::vec3(0.2, 0, 0.6))
{
}

void SceneCloth::initScene()
{
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(PRIM_RESTART);

	compileAndLinkShader();
	initBuffers();

	projection = glm::perspective(glm::radians(50.0f), (float)width / height, 1.0f, 100.0f);
	renderProg.use();
	setLight();

	computeProg.use();
	float dx = clothSize.x / (nParticles.x - 1);
	float dy = clothSize.y / (nParticles.y - 1);
	computeProg.setUniform("RestLengthHoriz", dx);
	computeProg.setUniform("RestLengthVert", dy);
	computeProg.setUniform("RestLengthDiag", sqrtf(dx * dx + dy * dy));

	glActiveTexture(GL_TEXTURE0);
	clothTexture = Texture::loadTexture("../res/texture/textile.png");
}

void SceneCloth::initBuffers()
{
	// Initial transform
	glm::mat4 transf = glm::translate(glm::mat4(1.0), glm::vec3(0, clothSize.y, 0));
	transf = glm::rotate(transf, glm::radians(-80.0f), glm::vec3(1, 0, 0));
	transf = glm::translate(transf, glm::vec3(0, -clothSize.y, 0));

	// Initial positions of the particles
	vector<GLfloat> initPos;
	vector<GLfloat> initVel(nParticles.x * nParticles.y * 4, 0.0f);
	vector<float> initTc;
	float dx = clothSize.x / (nParticles.x - 1);
	float dy = clothSize.y / (nParticles.y - 1);
	float ds = 1.0f / (nParticles.x - 1);
	float dt = 1.0f / (nParticles.y - 1);
	glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < nParticles.y; i++) {
		for (int j = 0; j < nParticles.x; j++) {
			p.x = dx * j;
			p.y = dy * i;
			p.z = 0.0f;
			p = transf * p;
			initPos.push_back(p.x);
			initPos.push_back(p.y);
			initPos.push_back(p.z);
			initPos.push_back(1.0f);

			initTc.push_back(ds * j);
			initTc.push_back(dt * i);
		}
	}

	// Every row is one triangle strip
	vector<GLuint> el;
	for (int row = 0; row < nParticles.y - 1; row++) {
		for (int col = 0; col < nParticles.x; col++) {
			el.push_back((row + 1) * nParticles.x + (col));
			el.push_back((row)*nParticles.x + (col));
		}
		el.push_back(PRIM_RESTART);
	}

	// We need buffers for position (2), element index,
	// velocity (2), normal, and texture coordinates.
	GLuint bufs[7];
	glGenBuffers(7, bufs);
	posBufs[0] = bufs[0];
	posBufs[1] = bufs[1];
	velBufs[0] = bufs[2];
	velBufs[1] = bufs[3];
	normBuf = bufs[4];
	elBuf = bufs[5];
	tcBuf = bufs[6];

	GLuint parts = nParticles.x * nParticles.y;

	// The buffers for positions
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBufs[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, parts * 4 * sizeof(GLfloat), &initPos[0], GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, posBufs[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, parts * 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	// Velocities
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, velBufs[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, parts * 4 * sizeof(GLfloat), &initVel[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, velBufs[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, parts * 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);

	// Normal buffer
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, normBuf);
	glBufferData(GL_SHADER_STORAGE_BUFFER, parts * 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);

	// Element indicies
	glBindBuffer(GL_ARRAY_BUFFER, elBuf);
	glBufferData(GL_ARRAY_BUFFER, el.size() * sizeof(GLuint), &el[0], GL_DYNAMIC_COPY);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, tcBuf);
	glBufferData(GL_ARRAY_BUFFER, initTc.size() * sizeof(GLfloat), &initTc[0], GL_STATIC_DRAW);

	numElements = GLuint(el.size());

	// Set up the VAO
	glGenVertexArrays(1, &clothVao);
	glBindVertexArray(clothVao);

	glBindBuffer(GL_ARRAY_BUFFER, posBufs[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, tcBuf);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elBuf);
	glBindVertexArray(0);
}

void SceneCloth::update(float t)
{
	if (time == 0.0f) {
		deltaT = 0.0f;
	}
	else {
		deltaT = t - time;
	}
	time = t;

}

void SceneCloth::render()
{
	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	computeProg.use();
	setPhysics();

	for (int i = 0; i < 1000; i++) {
		glDispatchCompute(nParticles.x / 10, nParticles.y / 10, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		// Swap buffers
		readBuf = 1 - readBuf;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBufs[readBuf]);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, posBufs[1 - readBuf]);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, velBufs[readBuf]);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, velBufs[1 - readBuf]);
	}

	// Compute the normals
	computeProgNorm.use();
	glDispatchCompute(nParticles.x / 10, nParticles.y / 10, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	// Now draw the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderProg.use();
	setLight();

	renderProg.setTexture("Tex", clothTexture, 0);

	view = glm::lookAt(glm::vec3(3, 2, 5), glm::vec3(2, 1, 0), glm::vec3(0, 1, 0));
	model = glm::mat4(1.0f);
	setMatrices();

	// Draw the cloth
	glBindVertexArray(clothVao);
	glDrawElements(GL_TRIANGLE_STRIP, numElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void SceneCloth::setMatrices() {
	glm::mat4 mv = view * model;
	glm::mat3 norm = glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));

	renderProg.setUniform("ModelViewMatrix", mv);
	renderProg.setUniform("NormalMatrix", norm);
	renderProg.setUniform("MVP", projection * mv);
}

void SceneCloth::setLight()
{
	renderProg.setUniform("LightPosition", glm::vec4(lightDir, 1.0f));
	renderProg.setUniform("LightIntensity", lightColor);
	renderProg.setUniform("Kd", glm::vec3(diffuse));
	renderProg.setUniform("Ka", glm::vec3(ambiant));
	renderProg.setUniform("Ks", glm::vec3(specularity));
	renderProg.setUniform("Shininess", shininess);
}

void SceneCloth::setPhysics()
{
	computeProg.setUniform("Gravity", gravity);
	computeProg.setUniform("ParticleMass", particleMass);
	computeProg.setUniform("SpringK", springK);

	computeProg.setUniform("HasWind", static_cast<float>(wind));
	computeProg.setUniform("WindStrength", windStrength);
	computeProg.setUniform("WindDir", windDir);
}

void SceneCloth::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(50.0f), (float)width / height, 1.0f, 100.0f);
}

void SceneCloth::uiUpdate()
{
	ImGui::Begin("GUI");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("Wireframe", &wireframe);
	if (ImGui::CollapsingHeader("Particles", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SliderFloat3("Gravity", &gravity[0], -20.0f, 20.0f);
		ImGui::SliderFloat("ParticleMass", &particleMass, 0.1f, 0.5f);
		ImGui::SliderFloat("SpringK", &springK, 500.0f, 5000.0f);
	}

	if (ImGui::CollapsingHeader("Wind", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Checkbox("Enable", &wind);
		ImGui::SliderFloat("Strength", &windStrength, 0.0f, 10.0f);
		ImGui::SliderFloat3("Wind Direction", &windDir[0], -1.0f, 1.0f);
	}

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SliderFloat3("Light Direction", &lightDir[0], 0.0f, 1.0f);
		ImGui::ColorPicker3("Color", &lightColor[0]);
		ImGui::SliderFloat("Ambiant", &ambiant, 0.0f, 1.0f);
		ImGui::SliderFloat("Diffuse", &diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular", &specularity, 0.0f, 1.0f);
		ImGui::SliderFloat("Shininess", &shininess, 0.0f, 200.0f);
	}
	
	ImGui::End();
}

void SceneCloth::compileAndLinkShader()
{
	try {
		renderProg.compileShader("shader/ads_vs.glsl");
		renderProg.compileShader("shader/ads_fs.glsl");
		renderProg.link();

		computeProg.compileShader("shader/cloth_cs.glsl");
		computeProg.link();

		computeProgNorm.compileShader("shader/cloth_normal_cs.glsl");
		computeProgNorm.link();
	}
	catch (GLSLProgramException& e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}
