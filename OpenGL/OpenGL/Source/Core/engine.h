#pragma once

#include <SDL.h>
#include <glad\glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>
#include <map>
#include <vector>

#include "timer.h"
#include "input.h"
#include "file_system.h"
#include "renderer/renderer.h"
#include "math/transform.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Update();
	
	template <typename T>
	T* Get()
	{
		for (System* system : m_systems)
		{
			if (dynamic_cast<T*>(system) != nullptr)
			{
				return static_cast<T*>(system);
			}
		}
		return nullptr;
	}

	bool ForceQuit() { return m_quit; }

private:
	std::vector<class System*> m_systems;
	bool m_quit = false;
};