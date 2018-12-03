#pragma once
#include "core/scene.h"

class Scene10 : public Scene
{
public:
	Scene10(class Engine* engine) : Scene(engine) {}
	virtual ~Scene10() {}

	bool Initialize() override;
	void Shutdown() override;
	void Update() override;
	void Render() override;

	const char* Name() override { return "Scene08"; }

private:
	int m_lightIndex = 0;
	GLuint m_framebuffer;
	
};


