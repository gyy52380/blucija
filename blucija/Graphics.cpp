#include "stdafx.h"
#include "Graphics.h"
#include "GLProgram.h"
#include "Quad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <cstddef>
#include <vector>

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\string_cast.hpp>

namespace gl
{

GLProgram program;

GLuint vao;
GLuint vbo;
GLuint quadVBO;
GLuint quadIBO;

uint32 n_of_instances_to_draw;

void init_camera(float left, float right, float bottom, float top)
{
	program.use();

	glm::mat4 cameraMatrix = glm::ortho(left, right, bottom, top);
	GLint cameraLocation = program.setUniformLocation("cameraMatrix");

	if (cameraLocation == -1)
		printf("Can't create uniform location for camera matrix\n");
	else
		glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	program.disable();
}

GLuint create_texture(const char* texture_path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int image_width, image_height, n_components;
	unsigned char *image_data = stbi_load(texture_path, &image_width, &image_height, &n_components, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D); //no need for mipmaps for 2D, if you include mipmaps change MIN/MAG_FILTER

	stbi_image_free(image_data);
	return textureID;
}

void create_base_quad(float quad_width, float quad_height)
{
	glBindVertexArray(vao);

	//make & fill element buffer
	uint8 indices[6] = { 0, 1, 2, 1, 2, 3 };

	glGenBuffers(1, &quadIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8) * 6, indices, GL_STATIC_DRAW);

	//make & fill vertex buffer
	Quad baseQuad;
	baseQuad.init(glm::vec2(0, 0), quad_width, quad_height);
	baseQuad.setUV(glm::vec2(0, 0), 16, 16);
	Vertex quadVertices[4] =
	{ baseQuad.bottomLeft, baseQuad.bottomRight, baseQuad.topLeft, baseQuad.topRight };

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, quadVertices, GL_STATIC_DRAW);

	//set the array attribs for constant quad vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
}

void update_translation_buffer_data(std::vector<Vertex> const &vertices)
{
	n_of_instances_to_draw = vertices.size();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

	//unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init(uint32 screen_width, uint32 screen_height)
{
	program.addShader("../data/shaders/vertex_shader.vert", GL_VERTEX_SHADER);
	program.addShader("../data/shaders/fragment_shader.frag", GL_FRAGMENT_SHADER);
	program.compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	create_base_quad(1.0f, 1.0f);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//call fillbuffer() from elsewhere

	//set array attribs for translation vectors changing once per instance
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribDivisor(2, 1); //maybe attribpointers need to first be enabled for this to work?
	glVertexAttribDivisor(3, 1);

	init_camera(0, screen_width/20, 0, screen_height/20); //pixels_per_column = 100
	create_texture("../data/textures/tetris_cubes.png");

	//unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cleanup()
{
	program.destroy();
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &quadVBO);
	glDeleteBuffers(1, &quadIBO);
	glDeleteVertexArrays(1, &vao);
}

void clear_screen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(72.0f / 255.0f, 76.0f / 255.0f, 104.0f / 255.0f, 1.0f);
}

void draw(SDL_Window *window_handle)
{
	glBindVertexArray(vao);
	program.use();

	for (int i = 0; i <= 3; ++i) glEnableVertexAttribArray(i);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0, n_of_instances_to_draw);

	SDL_GL_SwapWindow(window_handle);

	for (int i = 0; i <= 3; ++i) glDisableVertexAttribArray(i);

	glBindVertexArray(0);
	program.disable();
}

}