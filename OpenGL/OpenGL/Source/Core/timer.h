#pragma once
#include "system.h"
#include "engine.h"

class Timer : public System
{
public:
	Timer(class Engine* engine) : System(engine) {}
	virtual ~Timer() {}

	bool Initialize();
	void Shutdown();
	void Update();

	const char* Name() override { return "Timer"; }

	void Reset();
	
	float DeltaTime() const { return m_dt * m_timeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	float FPS() const { return m_fps; } //

	void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	float GetTimeScale() const { return m_timeScale; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }
	bool IsPaused() const { return m_paused; }

private:
	float m_fps;
	float m_dt;
	float m_timeScale;
	int m_frameCounter;
	Uint32 m_prevTicks;
	Uint32 m_startTicks;
	bool m_paused;
	const int FRAME_COUNT = 100;
};