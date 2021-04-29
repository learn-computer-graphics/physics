#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
	static GLuint loadTexture(const std::string& fName);
	static GLuint loadCubeMap(const std::string& baseName, const std::string& extention = ".png");
	static GLuint loadHdrCubeMap(const std::string& baseName);
	static unsigned char* loadPixels(const std::string& fName, int& w, int& h, bool flip = true);
	static void deletePixels(unsigned char*);
};
