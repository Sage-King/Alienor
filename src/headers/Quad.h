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
		//sprite size in pixels. width, height, size, and location in normalized screen space (bot left -1.0,-1.0, top right 1.0,1.0), x and y are center of the quad so make sure you divide width and height by 2.0 when adding to the center to get the edges of the quad
		Quad(const std::string& filepath, unsigned int size_of_sprite_x, unsigned int size_of_sprite_y, double width, double height, double in_x, double in_y);
		Quad();
		                       
		void draw();

		static bool are_quads_intersecting(const Quad* quad_1, const Quad* quad_2)
		{
			double x_edge = quad_1->x + (quad_1->width / 2);
			double neg_x_edge = quad_1->x - (quad_1->width / 2);
			double y_edge = quad_1->y + (quad_1->height / 2);
			double neg_y_edge = quad_1->y - (quad_1->height / 2);

			double in_x_edge = quad_2->x + (quad_2->width / 2);
			double in_neg_x_edge = quad_2->x - (quad_2->width / 2);
			double in_y_edge = quad_2->y + (quad_2->height / 2);
			double in_neg_y_edge = quad_2->y - (quad_2->height / 2);

			return (neg_x_edge < in_x_edge&& x_edge > in_neg_x_edge &&
				in_neg_y_edge < y_edge&& in_y_edge > neg_y_edge);
		}
		const bool is_intersecting(const Quad* quad_2) const 
		{
			double x_edge = x + (width / 2);
			double neg_x_edge = x - (width / 2);
			double y_edge = y + (height / 2);
			double neg_y_edge = y - (height / 2);

			double in_x_edge = quad_2->x + (quad_2->width / 2);
			double in_neg_x_edge = quad_2->x - (quad_2->width / 2);
			double in_y_edge = quad_2->y + (quad_2->height / 2);
			double in_neg_y_edge = quad_2->y - (quad_2->height / 2);

			return (neg_x_edge < in_x_edge&& x_edge > in_neg_x_edge &&
				in_neg_y_edge < y_edge&& in_y_edge > neg_y_edge);
		}
		double get_right_edge() { return x + (width / 2.0); }
		double get_left_edge() { return x - (width / 2.0); }
		double get_bottom_edge() { return y + (height / 2.0); }
		double get_top_edge() { return y - (height / 2.0); }

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