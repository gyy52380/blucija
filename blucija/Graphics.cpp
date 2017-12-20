#include "stdafx.h"
#include "Graphics.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <cstddef>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

typedef std::pair<GLuint, std::vector<glm::vec2>> render_pair;
std::vector<render_pair> render_batches;

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
}

void clear_screen()
{
	static float background_color[4] =
	{ 72.0f / 255.0f, 76.0f / 255.0f, 104.0f / 255.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
}

void add_batch(std::vector<glm::vec2> trans_vec, GLuint textureID)
{
	render_batches.push_back(render_pair(textureID, trans_vec));
}

void draw(SDL_Window *window_handle)
{
	clear_screen();

	glBindVertexArray(vao);
	shader_program.use();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, translation_vbo);
	
	for (auto &batch : render_batches)
	{
		glBindTexture(GL_TEXTURE_2D, batch.first);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * batch.second.size(), batch.second.data(), GL_STATIC_DRAW); //maybe dynamic

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, batch.second.size());

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	render_batches.clear();

	SDL_GL_SwapWindow(window_handle);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	shader_program.disable();
}

textureID create_texture(const char* texture_path)
{
	textureID textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int image_width, image_height, n_components;
	unsigned char *image_data = stbi_load(texture_path, &image_width, &image_height, &n_components, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	if (glGetError())
		printf("Can't load texture: %s; openGL error: %i", texture_path, glGetError());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D); //no need for mipmaps for 2D, if you include mipmaps change MIN/MAG_FILTER

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image_data);

	return textureID;
}

void cleanup()
{
	shader_program.destroy();
	glDeleteBuffers(1, &translation_vbo);
	glDeleteBuffers(1, &quad_vbo);
	glDeleteVertexArrays(1, &vao);
}

}