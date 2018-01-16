#include "stdafx.h"
#include "Graphics.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <cstddef>
#include <vector>
#include <cstdio>

#include "GLProgram.h"
#include "Vertex.h"
#include "Quad.h"
#include "Entity.h"

// for debugging, replace later with logging
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\string_cast.hpp>


namespace gl
{


GLProgram shader_program;

GLuint vao;
GLuint quad_vbo;
GLuint translation_vbo;

void init_camera(float left, float right, float bottom, float top)
{
	shader_program.use();

	glm::mat4 cameraMatrix = glm::ortho(left, right, bottom, top);
	GLint cameraLocation = shader_program.setUniformLocation("camera_matrix");

	if (cameraLocation == -1)
		printf("Can't create uniform location for camera matrix\n");
	else
		glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	shader_program.disable();
}

void create_instance_quad(float q_width, float q_height, GLuint *quad_vbo)
{
	Quad instance_quad(q_width, q_height);
	instance_quad.bottomLeft.uv		= glm::vec2(0, 0);
	instance_quad.bottomRight.uv	= glm::vec2(1, 0);
	instance_quad.topLeft.uv		= glm::vec2(0, 1);
	instance_quad.topRight.uv		= glm::vec2(1, 1);

	Vertex quad_vertices[6] =
	{
		instance_quad.bottomLeft,
		instance_quad.topLeft,
		instance_quad.bottomRight,

		instance_quad.bottomRight,
		instance_quad.topLeft,
		instance_quad.topRight
	};

	glGenBuffers(1, quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW); //sizeof(quad_vertices) == sizeof(Vertex) * 6

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void enable_blending()
{
	glEnable(GL_BLEND);
	if (uint32 error = glGetError())
		printf("Blending. Error code: %i\n", error);
	glBlendEquation(GL_FUNC_ADD);
	if (uint32 error = glGetError())
		printf("Blend eq. Error code: %i\n", error);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (uint32 error = glGetError())
		printf("Blend func. Error code: %i\n", error);
}

void init(uint32 camera_scale_x, uint32 camera_scale_y)
{
	shader_program.addShader("../data/shaders/vertex_shader.vert", GL_VERTEX_SHADER);
	shader_program.addShader("../data/shaders/fragment_shader.frag", GL_FRAGMENT_SHADER);
	shader_program.compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//quad
	create_instance_quad(1.0f, 1.0f, &quad_vbo);
	//quad

	glGenBuffers(1, &translation_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, translation_vbo);

	//call fillbuffer() from elsewhere

	//set array attribs for translation vectors changing once per instance
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glVertexAttribDivisor(2, 1);

	init_camera(0, camera_scale_x, 0, camera_scale_y); //pixels_per_column = 20?

	//unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	enable_blending(); //for transparency
	
}

void clear_screen()
{
	static float background_color[4] =
	{ 72.0f / 255.0f, 76.0f / 255.0f, 104.0f / 255.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
}

void draw_quads(SDL_Window *window_to_draw, GLuint texID, glm::vec2 *array_ptr, uint32 n_elements)
{
	glBindVertexArray(vao);
	shader_program.use();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	////
	glBindBuffer(GL_ARRAY_BUFFER, translation_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * n_elements,
		array_ptr, GL_DYNAMIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texID);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, n_elements);

	glBindTexture(GL_TEXTURE_2D, 0);
	////

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	shader_program.disable();
}

void swap_screen_buffer(SDL_Window *window_to_swap)
{
	SDL_GL_SwapWindow(window_to_swap);
}

void cleanup()
{
	shader_program.destroy();
	glDeleteBuffers(1, &translation_vbo);
	glDeleteBuffers(1, &quad_vbo);
	glDeleteVertexArrays(1, &vao);
}

}