#include "Player.h"

#include <iostream>
#include <unordered_map>
#include <memory>

namespace Sage 
{
	Player::Player()
		:
		Game_Actor("main_player", 3, Quad{ "resources\\test_blue_crack.png", 100,100, 0.25f,0.125f,0.75f,0.75f })
	{
		last_change = glfwGetTime();
	}

	Player::~Player()
	{

	}

	void Player::draw()
	{
		quad.draw();
	}
	void Player::update(double delta_time)
	{
		if ((glfwGetTime() - last_change) >= 0.041666)
		{
			quad.sprite_number_x++;
			last_change = glfwGetTime();
		}
	}

	void Player::move_up(double delta_time)
	{
		quad.y -= 1.0 * delta_time;
	}
	void Player::move_down(double delta_time)
	{
		quad.y += 1.0 * delta_time;
	}
	void Player::move_left(double delta_time)
	{
		quad.x -= 1.0 * delta_time;
	}
	void Player::move_right(double delta_time)
	{
		quad.x += 1.0 * delta_time;
	}
}