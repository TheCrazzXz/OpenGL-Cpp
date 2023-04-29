#pragma once

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "glad/glad.h"

class Renderer
{
public:
	void prepare()
	{
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void render(RawModel model)
	{
		glBindVertexArray(model.getVaoID());
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
};

#endif