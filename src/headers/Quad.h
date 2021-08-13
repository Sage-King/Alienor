#ifndef QUAD_H_GUARD
#define QUAD_H_GUARD

#include "glm/glm.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <Texture.h>
#include <string>
namespace Sage
{
	class Quad
	{
	public:
		Quad(glm::vec4 color, double width, double height, double in_x, double in_y);
		Quad(const std::string& filepath, int size_of_sprite_x, int size_of_sprite_y, double width, double height, double in_x, double in_y);
		Quad();
		                       
		void draw();
		bool isIntersecting(Quad in_quad);

		glm::vec4 getColor();
		void setColor(glm::vec4 in_color);
		double x;
		double y;
		unsigned int sprite_number_x;
		unsigned int sprite_number_y;
		double width;
		double height;

	private:
		Texture texture;
		Shader shader;
		glm::vec4 color = glm::vec4{ 1.0f,1.0f,1.0f,1.0f };
		unsigned int vao;
		bool is_textured = false;
	};
}
#endif