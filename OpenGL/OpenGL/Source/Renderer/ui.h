#pragma once
#include "core/engine.h"

class UI : public System
{
public:
	UI(Engine* engine);

	bool Initialize() override;
	void Shutdown() override;
	void Update() override;

	void Draw();

	void Start();
	void End();

	const char* Name() { return "UI"; }

	static bool VectorOfStringGetter(void* data, int n, const char** out_text);
};