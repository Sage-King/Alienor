#include "Alienor.h"

#include "Texture.h"
#include "Quad.h"
#include "Bucket_Vector.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Booster.h"
#include "Ender.h"
namespace Sage
{
	Alienor::Alienor(GLFWwindow* window)
		:
		background_color(glm::vec4(0.0f, 0.1f, 0.1f, 1.0f)),
		input_handler(window),
		window(window)
	{ 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Menu_Button play_button("main_menu_play_button", 3, "resources\\start.png", 300, 100, 0.6, 0.2, 0.5, 0.5, [this]() {game_state++; });
		reg_menu_object(std::make_shared<Menu_Button>(play_button));

		//consider doing a thread pool to register these objects while the menu screen runs
		//RNG for positions of enders and boosters
		rng = std::mt19937(rand_device());
		pos_distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);

		Booster booster_test{ pos_distribution(rng), 0.2, 0.175, 0.3, 2 };
		auto booster_temp_ptr = std::make_shared<Booster>(booster_test);
		reg_obj(booster_temp_ptr);
		reg_booster(booster_temp_ptr);

		Ender ender_test{ pos_distribution(rng), 0.0, 0.175, 0.3, 3 };
		auto ender_temp_ptr = std::make_shared<Ender>(ender_test);
		reg_obj(ender_temp_ptr);
		reg_ender(ender_temp_ptr);

		Player player;
		auto player_temp_ptr = std::make_shared<Player>(player);
		reg_obj(player_temp_ptr);
		reg_game_actor(player_temp_ptr);
	}


	void Alienor::process_inputs()
	{
		std::vector<Command*> commands = input_handler.retrieve_input();
		
		for (int i = 0; i < all_game_actors.size(); i++)
		{
			for (int j = 0; j < commands.size(); j++)
			{
				commands[j]->execute(all_game_actors[i], delta_time);
			}
			
		}
	}
	void Alienor::process_collisions()
	{
		//enders collision
		for (int i = 0; i < all_enders.size(); i++)
		{
			for (int j = 0; j < all_game_actors.size(); j++)
			{
				if (all_enders[i]->get_quad()->is_intersecting(all_game_actors[j]->get_quad()))
				{
#if _DEBUG
					std::cout << "ender collided\n";
#endif // _DEBUG
				}
			}
			
		}

		//boosters collision
		for (int i = 0; i < all_boosters.size(); i++)
		{
			for (int j = 0; j < all_game_actors.size(); j++)
			{
				if (all_boosters[i]->get_quad()->is_intersecting(all_game_actors[j]->get_quad()))
				{
#if _DEBUG
					std::cout << "booster collided\n";
#endif // _DEBUG
				}
			}

		}
	}
	void Alienor::update()
	{
		double current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		switch (game_state)
		{
		case 0:
			//button inputs for main menu handled in mouse_button_callback (so we don't get multiple inputs by accident)
			break;
		case 1:
			process_inputs();
			process_collisions();
			
			for (int i = 0; i < all_objects.get_full_list().size(); i++)
			{
				all_objects.get_full_list()[i]->update(delta_time);
			}
			for (int i = 0; i < all_boosters.size(); i++)
			{
				if (all_boosters[i]->is_marked_for_death())
				{
#if _DEBUG
					std::cout << "booster deleted\n";
#endif // _DEBUG
					all_boosters.erase(all_boosters.begin() + i);
				}
			}
			break;
		default:
			std::cout << "\n\n Impressive that you broke the game. Good job, please make an issue on Sage King's Github and let's chat. :) (Seriously, you're not in trouble, but I'm curious how you broke it.) ERR: game_state wasn't valid.\n";
			set_valid_exit(false);
			glfwSetWindowShouldClose(window, true);
			break;
		}
			
	}
	void Alienor::draw()
	{
		switch (game_state)
		{
		case 0:
			for (int i = 0; i < all_menu_buttons.get_full_list().size(); i++)
			{
				all_menu_buttons.get_full_list()[i]->draw();
			}
			break;
		case 1:
			glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			for (int i = 0; i < all_objects.get_full_list().size(); i++)
			{
				all_objects.get_full_list()[i]->draw();
			}
			break;
		default:
			std::cout << "\n\n Impressive that you broke the game. Good job, please make an issue on Sage King's Github and let's chat. :) (Seriously, you're not in trouble, but I'm curious how you broke it.) ERR: game_state wasn't valid.\n";
			set_valid_exit(false);
			glfwSetWindowShouldClose(window, true);
			break;
		}
		
	}


	void Alienor::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
			valid_exit = true;
		}
		if (mods == GLFW_MOD_SHIFT && action == GLFW_PRESS)
		{
			game_state++;
		}
	}

	void Alienor::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (game_state == 0)
		{

			if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
			{

				double x_pos, y_pos;
				glfwGetCursorPos(window, &x_pos, &y_pos);
				//have to normalize the x and y pos
				int width, height;
				glfwGetFramebufferSize(window, &width, &height);
				x_pos /= width;
				y_pos /= height;
				for (int i = 0; i < all_menu_buttons.get_full_list().size(); i++)
				{
					Quad* temp_quad = all_menu_buttons.get_full_list()[i]->get_quad();
					//check if mouse is in menu button
					if (x_pos >= temp_quad->x - (temp_quad->width) / 2.0 &&
						x_pos <= temp_quad->x + (temp_quad->width) / 2.0 &&
						y_pos >= temp_quad->y - (temp_quad->height) / 2.0 &&
						y_pos <= temp_quad->y + (temp_quad->height) / 2.0)
					{
						all_menu_buttons.get_full_list()[i]->execute();
					}
				}
			}
		}
	}

	//these are all almost identical, just which array it's pointing to
	//after writing the comment above this, I feel like there's a template solution to this lmao
	//I'm not going to figure it out, but I feel like there is one :P
	void Alienor::reg_obj(std::shared_ptr<Object> obj)
	{
		for (int i = 0; i < all_objects.get_full_list().size(); i++)
		{
			if (obj->get_name() == all_objects.get_full_list()[i]->get_name())
			{
				std::cout << "Name conflict: " + obj->get_name() + " between object: " + std::to_string(obj->get_ID()) + " and object: " + std::to_string(all_objects.get_full_list()[i]->get_ID()) + '\n';
				return;
			}
		}
		all_objects.insert(obj, obj->get_draw_layer());
	}
	void Alienor::reg_booster(std::shared_ptr<Booster> booster)
	{
		for (int i = 0; i < all_boosters.size(); i++)
		{
			if (booster->get_name() == all_boosters[i]->get_name())
			{
				std::cout << "Name conflict: " + booster->get_name() + " between object: " + std::to_string(booster->get_ID()) + " and object: " + std::to_string(all_boosters[i]->get_ID()) + '\n';
				return;
			}
		}
		all_boosters.push_back(booster);
	}
	void Alienor::reg_ender(std::shared_ptr<Ender> ender)
	{
		for (int i = 0; i < all_enders.size(); i++)
		{
			if (ender->get_name() == all_enders[i]->get_name())
			{
				std::cout << "Name conflict: " + ender->get_name() + " between object: " + std::to_string(ender->get_ID()) + " and object: " + std::to_string(all_enders[i]->get_ID()) + '\n';
				return;
			}
		}
		all_enders.push_back(ender);
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

	void Alienor::reg_menu_object(std::shared_ptr<Menu_Button> menu_button)
	{
		for (int i = 0; i < all_menu_buttons.get_full_list().size(); i++)
		{
			if (menu_button->get_name() == all_objects.get_full_list()[i]->get_name())
			{
				std::cout << "Name conflict: " + menu_button->get_name() + " between object: " + std::to_string(menu_button->get_ID()) + " and object: " + std::to_string(all_objects.get_full_list()[i]->get_ID()) + '\n';
				return;
			}
		}
		all_menu_buttons.insert(menu_button, menu_button->get_draw_layer());
	}
}
