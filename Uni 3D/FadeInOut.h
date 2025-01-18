#pragma once
#include "Renderer.h"

enum FadeType
{
	None,
	In,
	Out
};

class FadeInOut
{
public:
	FadeInOut()
	{
		Reset();
	}
	void Update();

	FadeType fadeType;
private:
	void Reset();
	float t;
};

extern FadeInOut fadeInOut;