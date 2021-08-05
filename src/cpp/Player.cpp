#include "Player.h"

#include <Texture.h>
#include <Quad.h>
#include <iostream>
namespace Sage
{
	Player::Player()
		:
		Object("main_player")
	{
		Sage::Texture test_texture{ "resources\\test_blue_crack.png", 100, 100 };
		Sage::Quad test_quad{ test_texture, 0.1f, 0.25f, 0.5f, 0.5f };
	}

	Player::~Player()
	{

	}

	void Player::draw(GLFWwindow* window)
	{
		std::cout << "draw";
	}
	void Player::update(GLFWwindow* window)
	{
		std::cout << "update";
	}
}