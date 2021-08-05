#ifndef QUAD_H_GUARD
#define QUAD_H_GUARD

#include "glm/glm.hpp"
#include "Shader.h"
#include <Texture.h>

namespace Sage
{
	class Quad
	{
	public:
		Quad(glm::vec3 color, float width, float height, float in_x, float in_y);
		Quad(Texture texture, float width, float height, float in_x, float in_y);

		void draw();
		bool isIntersecting(Quad in_quad);

		float getWidth();
		void setWidth(float in_width);
		float getHeight();
		void setHeight(float in_height);
		glm::vec3 getColor();
		void setColor(glm::vec3 in_color);
		float x;
		float y;
		unsigned int sprite_number_x;
		unsigned int sprite_number_y;

	private:
		glm::vec3 color;
		float width;
		float height;
		Shader shader;
		unsigned int vao;
		Texture texture;
		bool is_textured = false;
	};
}
#endif