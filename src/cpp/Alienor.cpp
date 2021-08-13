#include "Alienor.h"

#include "Texture.h"
#include "Quad.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Player.h"
#include "Obstacle.h"
namespace Sage
{
	Alienor::Alienor(GLFWwindow* window)
		:
		background_color(glm::vec4(0.0f,0.1f,0.1f,1.0f)),
		i_handler(window)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Obstacle miss_fortune{"resources\\miss_fortune.jpg", 1000,1000,0.5,0.5,0.5,0.5};
		auto miss_fortune_temp = std::make_shared<Obstacle>(miss_fortune);
		reg_obj(miss_fortune_temp);
		reg_collidable(miss_fortune_temp);
		Obstacle pikachu{"resources\\pikachu.png", 1000,1000,0.1,0.1,0.1,0.1};
		auto pikachu_temp = std::make_shared<Obstacle>(pikachu);
		reg_obj(pikachu_temp);
		reg_collidable(pikachu_temp);
		Player main_player{}; 
		auto player_temp = std::make_shared<Player>(main_player);
		reg_obj(player_temp);
		reg_collidable(player_temp);
		reg_game_actor(player_temp);
	}

	void Alienor::update()
	{
		process_inputs();
		process_collisions();
		double current_frame = glfwGetTime();
	 	delta_time = current_frame - last_frame;
		last_frame = current_frame;
		for (int i = 0; i < all_objects.size(); i++)
		{
			all_objects[i]->update();
		}
	}
	void Alienor::draw()
	{
		glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		for (int i = 0; i < all_objects.size(); i++)
		{
			all_objects[i]->draw();
		}
	}

	void Alienor::process_inputs()
	{
		std::vector<Command*> current_inputs = i_handler.handle_input();
		for (int i = 0; i < current_inputs.size(); i++)
		{
			for (int j = 0; j < all_game_actors.size(); j++)
			{
				current_inputs[i]->execute(all_game_actors[j], delta_time);
			}
		}
	}

	void Alienor::process_collisions()
	{
		for (int i = 0; i < all_collidables.size(); i++)
		{
			for (int j = 0; j < all_collidables.size(); j++)
			{
				//THIS IS WHERE YOU WERE, COLLISIONS BETWEEN ARBITRARY 2D OBJECTS
			}
		}
	}

	void Alienor::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}


	void Alienor::reg_obj(std::shared_ptr<Object> obj)
	{
		for (int i = 0; i < all_objects.size(); i++)
		{
			if (obj->get_name() == all_objects[i]->get_name())
			{
				std::cout << "Name conflict: " + obj->get_name() + " between object: " + std::to_string(obj->get_ID()) + " and object: " + std::to_string(all_objects[i]->get_ID()) + '\n';
				return;
			}
		}
		all_objects.push_back(obj);
	}
	void Alienor::reg_collidable(std::shared_ptr<Collidable> collidable)
	{
		for (int i = 0; i < all_collidables.size(); i++)
		{
			if (collidable->get_name() == all_collidables[i]->get_name())
			{
				std::cout << "Name conflict: " + collidable->get_name() + " between object: " + std::to_string(collidable->get_ID()) + " and object: " + std::to_string(all_collidables[i]->get_ID()) + '\n';
				return;
			}
		}
		all_collidables.push_back(collidable);
	}
	void Alienor::reg_game_actor(std::shared_ptr<Game_Actor> game_actor)
	{
		for (int i = 0; i < all_game_actors.size(); i++)
		{
			if (game_actor->get_name() == all_game_actors[i]->get_name())
			{
				std::cout << "Name conflict: " + game_actor->get_name() + " between object: " + std::to_string(game_actor->get_ID()) + " and object: " + std::to_string(all_game_actors[i]->get_ID()) + '\n';
				return;
			}
		}
		all_game_actors.push_back(game_actor);
	}
}
