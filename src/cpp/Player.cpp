#include "Player.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <algorithm>

namespace Sage 
{
	Player::Player()
		:
		Game_Actor("main_player", 3, Quad{ "resources\\pink_player.png", 300,300, 0.1f,0.1f,0.5f,0.75f })
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
		/*quad.y = std::clamp(quad.y, 0.0, 1.0);
		quad.x = std::clamp(quad.x, 0.0, 1.0);*/
	}

	constexpr double player_fast_speed = 6.0;
	constexpr double player_normal_speed = 1.0;

	void Player::move_up(double delta_time)
	{
		if (on_a_booster)
		{
			quad.y -= player_fast_speed * delta_time;
			return;
		}
		else
		{
			quad.y -= player_normal_speed * delta_time;
			return;
		}
	}
	void Player::move_down(double delta_time)
	{
		if (on_a_booster)
		{
			quad.y += player_fast_speed * delta_time;
			return;
		}
		else
		{
			quad.y += player_normal_speed * delta_time;
			return;
		}

	}
	void Player::move_left(double delta_time)
	{
		if (on_a_booster)
		{
			quad.x -= player_fast_speed * delta_time;
			return;
		}
		else
		{
			quad.x -= player_normal_speed * delta_time;
			return;
		}
	}
	void Player::move_right(double delta_time)
	{
		if (on_a_booster)
		{
			quad.x += player_fast_speed * delta_time;
			return;
		}
		else
		{
			quad.x += player_normal_speed * delta_time;
			return;
		}

	}
}