#include "scenerunner.h"
#include "scenecloth.h"

#include <memory>

int main(int argc, char* argv[])
{
	SceneRunner runner("Chapter 11 - cloth");
	std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new SceneCloth());
	return runner.run(std::move(scene));
}
