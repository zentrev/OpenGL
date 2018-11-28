#pragma once
#include "core/scene.h"

class Scene09 : public Scene
{
public:
	Scene09(class Engine* engine) : Scene(engine) {}
	virtual ~Scene09() {}

	bool Initialize() override;
	void Shutdown() override;
	void Update() override;
	void Render() override;

	const char* Name() override { return "Scene08"; }

private:
	int m_lightIndex = 0;
	GLuint m_framebuffer;
	
};


