#ifndef TEXTURE_H_GUARD
#define TEXTURE_H_GUARD

#include <glm/glm.hpp>
#include <string>
namespace Sage
{
	class Texture
	{
	//be nice; it's some of my earliest original code ;-;
	public:
		Texture(std::string filepath_relative, unsigned int stride_x, unsigned int stride_y);
		Texture();

		void Bind(); 
		void Update();
		const glm::vec2& get_top_left();
		const glm::vec2& get_bottom_right();
		const unsigned int& get_total_num_of_sprites_x();
		const unsigned int& get_total_num_of_sprites_y();
		int current_sprite_number_x, current_sprite_number_y;
		
	private:
		glm::vec2 top_left, bottom_right;
		unsigned int stride_x, stride_y;
		unsigned int total_num_of_sprites_x, total_num_of_sprites_y;
		unsigned int gl_texture_id;
		int width, height, channels;
	};
}
#endif