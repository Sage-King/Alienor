#include "Quad.h"
#include <algorithm>
#include <stb_image.h>
#include <filesystem>
#include "Texture.h"
namespace Sage
{
	Quad::Quad(glm::vec4 color, double width, double height, double in_x = 0.0, double in_y = 0.0)
	   :width(width),
		height(height),
		color(color),
		x(in_x),
		y(in_y),
		is_textured(false),
		sprite_number_x(0),
		sprite_number_y(0)
	{
		shader = Shader("shaders\\quad.vs", "shaders\\quad.fs");

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		float verts[] =
		{
			//pos
			-1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f,-1.0f,
			-1.0f,-1.0f
		};
		unsigned short indices[] =
		{
			0,1,2,
			0,2,3
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

	Quad::Quad(const std::string& filepath, int size_of_sprite_x, int size_of_sprite_y, double width, double height, double in_x = 0.0, double in_y = 0.0)
		:width(width),
		height(height),
		color(glm::vec4(1.0f,1.0f,1.0f,1.0f)),
		x(in_x),
		y(in_y),
		is_textured(true),
		sprite_number_x(0),
		sprite_number_y(0),
		texture(Texture(filepath, size_of_sprite_x, size_of_sprite_y))
	{
		shader = Shader("shaders\\quad_textured.vs", "shaders\\quad_textured.fs");
		shader.use();

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		float verts[] =
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f, 0.0f,
			-1.0f,-1.0f, 0.0f, 0.0f
		};
		unsigned short indices[] =
		{
			0,1,2,
			0,2,3
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

	Quad::Quad() {}

	void Quad::draw()
	{
		shader.use();

		glm::mat4 scale = glm::mat4(1.0f);
		scale = glm::scale(scale, glm::vec3(width, height, 0.0f));
		shader.setMat4("scale", scale);

		glm::mat4 translate = glm::mat4(1.0f);
		double temp_x = (x * 2) - 1;
		double temp_y = (y * 2) - 1;
		translate = glm::translate(translate, glm::vec3(temp_x, -temp_y, 0.0f));
		shader.setMat4("translate", translate);
		if (!is_textured)
		{
			shader.setVec4("color", color);
		}
		else
		{
 			texture.current_sprite_number_x = sprite_number_x;
			texture.current_sprite_number_y = sprite_number_y;
			texture.Update();
			shader.use();
			shader.setVec4("color", color);
			shader.setVec2("top_left", texture.get_top_left());
			shader.setVec2("bottom_right", texture.get_bottom_right());
			texture.Bind();
		}

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
		glBindVertexArray(0);
	}

	bool Quad::isIntersecting(Quad in_quad)
	{
		double x_edge = x + (width / 2);
		double neg_x_edge = x - (width / 2);
		double y_edge = y + (height / 2);
		double neg_y_edge = y - (height / 2);

		double in_x_edge = in_quad.x + (in_quad.width / 2);
		double in_neg_x_edge = in_quad.x - (in_quad.width / 2);
		double in_y_edge = in_quad.y + (in_quad.height / 2);
		double in_neg_y_edge = in_quad.y - (in_quad.height / 2);

		return (neg_x_edge < in_x_edge && x_edge > in_neg_x_edge && 
				in_neg_y_edge < y_edge && in_y_edge > neg_y_edge);
	}

	glm::vec4 Quad::getColor()
	{
		return color;
	}

	void Quad::setColor(glm::vec4 in_color)
	{
		color = in_color;
	}
}
