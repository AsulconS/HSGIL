/**
 * HSGIL - Handy Scalable Graphics Integration Library
 * Copyright (c) 2025 Adrian Bedregal
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <HSGIL/hsgil.hpp>

#include <iostream>

int main()
{
	gil::RenderingWindow window(800, 600, "Triangle");

	if(!window.isReady())
	{
		std::cerr << "Window is not ready, something went wrong" << std::endl;
		return -1;
	}

	gil::Shader shader("default");

	float data[] =
	{
		// Position
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f
	};

	gil::uint32 VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Timer Object with Debug Mode ON
	gil::Timer timer(true);
	while(window.isActive())
	{
		window.pollEvents();

		shader.use();

		glEnable(GL_SCISSOR_TEST);
		glBindVertexArray(VAO);

		glViewport(0, 0, 400, 300);
		glScissor(0, 0, 400, 300);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

		glViewport(400, 0, 400, 300);
		glScissor(400, 0, 400, 300);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

		glViewport(0, 300, 400, 300);
		glScissor(0, 300, 400, 300);
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

		glViewport(400, 300, 400, 300);
		glScissor(400, 300, 400, 300);
		glClearColor(0.175f, 0.175f, 0.175f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

		glBindVertexArray(0);
		glDisable(GL_SCISSOR_TEST);

		window.swapBuffers();
		timer.tick();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;
}
