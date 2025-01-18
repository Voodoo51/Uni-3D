#include "FadeInOut.h"

FadeInOut fadeInOut;

void FadeInOut::Reset()
{
	t = 0;
}

void FadeInOut::Update()
{
	if (fadeType == None)
	{
		return;
	}

	if (fadeType == In)
	{
		if (t >= 1)
		{
			fadeType = Out;
		}
		else
		{
			renderer.postprocessShader.setFloat("t", t);
			t += 5 * timer.deltaTime / 1000;
		}
	}
	else if (fadeType == Out)
	{
		if (t <= 0)
		{
			Reset();
			fadeType = None;
			renderer.postprocessShader.setFloat("t", 0);
		}
		else
		{
			renderer.postprocessShader.setFloat("t", t);
			t -= 5 * timer.deltaTime / 1000;
		}
	}
	
}