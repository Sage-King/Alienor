#include "Texture.h"
#include "stb_image.h"
#include <string>
#include <filesystem>
#include <GLFW/glfw3.h>
#include <iostream>
namespace Sage
{
	Texture::Texture(std::string filepath_relative, unsigned int stride_x_in_pixels, unsigned int stride_y_in_pixels)
		:
		stride_x(stride_x_in_pixels),
		stride_y(stride_y_in_pixels),
		total_num_of_sprites_x(1),
		total_num_of_sprites_y(1),
		gl_texture_id(0),
		width(0),
		height(0),
		channels(0),
		top_left(glm::vec2(0.0f)),
		bottom_right(glm::vec2(0.0f))
	{
		stbi_set_flip_vertically_on_load(true);

		std::string	picture_filepath = std::filesystem::current_path().string() + '\\' + filepath_relative;
		unsigned char* picture_data = stbi_load(picture_filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		glGenTextures(1, &gl_texture_id);
		glBindTexture(GL_TEXTURE_2D, gl_texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (picture_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, picture_data);
		}
		else
		{
			std::cout << "Failed to load texture from location: " + picture_filepath + "\n";
		}
		stbi_image_free(picture_data);

		if (stride_x > (unsigned int)width)
		{
		}
		else
			total_num_of_sprites_x = width / stride_x;
		if (stride_y > (unsigned int)height)
		{
		}
		else
			total_num_of_sprites_y = height / stride_y;
	}
	Texture::Texture()
	{
		std::cout << "[WARNING] Default texture constructor called. You should see a pink+black texture wherever it was called.\n";
		Texture("resources\\error.png", 100, 100);
	}

	void Texture::Update()
	{
		float x_calc;
		x_calc = stride_x * (float)(current_sprite_number_x % total_num_of_sprites_x);
		x_calc /= width;
		float y_calc;
		y_calc = stride_y * (float)(current_sprite_number_y % total_num_of_sprites_y);
		y_calc /= height;
		top_left.x = x_calc;
		top_left.y = y_calc;
		bottom_right.x = x_calc + ((float)stride_x / (float)width);
		bottom_right.y = y_calc + ((float)stride_y / (float)height);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, gl_texture_id);
	}

	const glm::vec2& Texture::get_top_left()
	{
		return top_left;
	}
	const glm::vec2& Texture::get_bottom_right()
	{
		return bottom_right;
	}
	const unsigned int& Texture::get_total_num_of_sprites_x()
	{
		return total_num_of_sprites_x;
	}
	const unsigned int& Texture::get_total_num_of_sprites_y()
	{
		return total_num_of_sprites_y;

	}
}