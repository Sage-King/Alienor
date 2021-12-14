#include "Alienor.h"

#include "Texture.h"
#include "Quad.h"
#include "Bucket_Vector.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Booster.h"
#include "Ender.h"
#include "macro_definitions.h"
#include <cstdio>
#include <cinttypes>

namespace Sage
{
	Alienor::Alienor(GLFWwindow* window)
		:
		game_background_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		main_menu_background_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		end_screen_background_color(glm::vec4(0.4f, 0.2f, 0.35f, 1.0f)),
		input_handler(window),
		window(window)
	{
		glEnable(GL_BLEND);                               
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Menu_Button play_button("main_menu_play_button", 3, "resources\\start.png", 300, 100, 0.6, 0.2, 0.5, 0.5, [this]() {game_state = 1; });
		reg_main_menu_object(std::make_shared<Menu_Button>(play_button));

		Menu_Button score_display("score_display", 4, "resources\\score.png", 300, 100, 0.15, 0.05, 0.1, 0.05, []() {});
		reg_static_display_object(std::make_shared<Menu_Button>(score_display));


		
		Menu_Button game_over_display("game_over_display", 3, "resources\\game_over.png", 600, 200, 0.6, 0.2, 0.5, 0.3, [](){});
		reg_end_screen_object(std::make_shared<Menu_Button>(game_over_display));
		
		Menu_Button restart_button("restart_button", 3, "resources\\restart.png", 300, 100, 0.3, 0.1, 0.5, 0.6, [this]() {game_state = 1; score = 0; });
		reg_end_screen_object(std::make_shared<Menu_Button>(restart_button));
		
		Menu_Button final_score_display("final_score_display", 3, "resources\\final_score.png", 600, 100, 0.6, 0.1, 0.4, 0.75, []() {});
		reg_end_screen_object(std::make_shared<Menu_Button>(final_score_display));



		//mersenne_rng for positions of enders and boosters
		mersenne_rng = std::mt19937(rand_device());
		pos_distribution_x = std::uniform_real_distribution<float>(0.0f, 1.0f);
		vel_distribution_y_booster = std::uniform_real_distribution<float>(0.3f, 0.7f);
		vel_distribution_y_ender = std::uniform_real_distribution<float>(0.3f, 1.0f);
		spawn_time_distribution_booster = std::uniform_real_distribution<float>(2.0f, 3.0f);
		spawn_time_distribution_ender   = std::uniform_real_distribution<float>(0.15f, 1.5f);
		size_distribution_booster = std::uniform_real_distribution<float>(0.15f, 0.3f);
		size_distribution_ender   = std::uniform_real_distribution<float>(0.05f, 0.35f);

		next_spawn_interval_booster = 1.0;
		next_spawn_interval_ender = 1.0;

		last_spawn_time_booster = glfwGetTime();
		last_spawn_time_ender = glfwGetTime();

		auto player_temp_ptr = std::make_shared<Player>(Player{});
		reg_obj(player_temp_ptr);
		reg_game_actor(player_temp_ptr);
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
			for (int i = 0; i < all_objects.get_full_list().size(); i++)
			{
				all_objects.get_full_list()[i]->update(delta_time);
			}
			process_inputs();
			process_collisions();
			clean_boosters_and_enders();
			spawn_boosters_and_enders();
#if _DEBUG & SCORE_DEBUG_PRINTOUT
			printf("Score: %" PRIdFAST64 "\n", score);
#endif
			break;
		case 2:
			//input handled in call back to prevent multiple inputs
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
				glClearColor(main_menu_background_color.x, main_menu_background_color.y, main_menu_background_color.z, main_menu_background_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				for (int i = 0; i < main_menu_objects.get_full_list().size(); i++)
				{
					main_menu_objects.get_full_list()[i]->draw();
				}
				break;
			case 1:
				glClearColor(game_background_color.x, game_background_color.y, game_background_color.z, game_background_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				for (int i = 0; i < static_display_objects.get_full_list().size(); i++)
				{
					static_display_objects.get_full_list()[i]->draw();
				}
				display_score_value_decimal(0.2, 0.05);
				for (int i = 0; i < all_objects.get_full_list().size(); i++)
				{
					all_objects.get_full_list()[i]->draw();
				}
				break;
			case 2:
				glClearColor(end_screen_background_color.x, end_screen_background_color.y, end_screen_background_color.z, end_screen_background_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				for (int i = 0; i < end_screen_objects.get_full_list().size(); i++)
				{
					end_screen_objects.get_full_list()[i]->draw();
				}
				display_score_value_decimal(0.65, 0.75);
				break;
			default:
				std::cout << "\n\n Impressive that you broke the game. Good job, please make an issue on Sage King's Github and let's chat. :) (Seriously, you're not in trouble, but I'm curious how you broke it.) ERR: game_state wasn't valid.\n";
				set_valid_exit(false);
				glfwSetWindowShouldClose(window, true);
				break;
			}

		}

	//calback functions
	void Alienor::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
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
	void Alienor::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
		switch (game_state)
		{
			case 0:
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
					for (int i = 0; i < main_menu_objects.get_full_list().size(); i++)
					{
						Quad* temp_quad = main_menu_objects.get_full_list()[i]->get_quad();
						//check if mouse is in menu button
						if (x_pos >= temp_quad->x - (temp_quad->width) / 2.0 &&
							x_pos <= temp_quad->x + (temp_quad->width) / 2.0 &&
							y_pos >= temp_quad->y - (temp_quad->height) / 2.0 &&
							y_pos <= temp_quad->y + (temp_quad->height) / 2.0)
						{
							main_menu_objects.get_full_list()[i]->execute();
						}
					}
				}
			}

			case 1:
				//input handled in Alienor::update
				break;

			case 2:
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
					for (int i = 0; i < end_screen_objects.get_full_list().size(); i++)
					{
						Quad* temp_quad = end_screen_objects.get_full_list()[i]->get_quad();
						//check if mouse is in menu button
						if (x_pos >= temp_quad->x - (temp_quad->width) / 2.0 &&
							x_pos <= temp_quad->x + (temp_quad->width) / 2.0 &&
							y_pos >= temp_quad->y - (temp_quad->height) / 2.0 &&
							y_pos <= temp_quad->y + (temp_quad->height) / 2.0)
						{
							end_screen_objects.get_full_list()[i]->execute();
						}
					}
				}
			}
			break;

			default:
			break;
		}
		}

	//these are all almost identical, just which array it's pointing to
	//after writing the comment above this, I feel like there's a template solution to this 
	//I'm not going to figure it out, but I feel like there is one :P
	//registration functions - puts a temporary object into a std::Vector in Alienor.h via a shared_ptr
	//this is how I kept track of all of the objects created and keep them alive
	//they get cleaned in clean_boosters_and_enders()
	void Alienor::reg_obj(std::shared_ptr<Object> obj)
	{
		if (all_objects.get_full_list().size() == 0)
		{
			all_objects.insert(obj, obj->get_draw_layer());
			return;
		}
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
		if (all_boosters.size() == 0)
		{
			all_boosters.push_back(booster);
			return;
		}
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
		if (all_enders.size() == 0)
		{
			all_enders.push_back(ender);
			return;
		}
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
		if (all_game_actors.size() == 0)
		{
			all_game_actors.push_back(game_actor);
			return;
		}
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
	
	void Alienor::reg_static_display_object(std::shared_ptr<Menu_Button> static_display_object)
	{
		if (static_display_objects.get_full_list().size() == 0)
		{
			static_display_objects.insert(static_display_object, static_display_object->get_draw_layer());
			return;
		}
		for (int i = 0; i < static_display_objects.get_full_list().size(); i++)
		{
			if (static_display_object->get_name() == all_objects.get_full_list()[i]->get_name())
			{
				std::cout << "Name conflict: " + static_display_object->get_name() + " between object: " + std::to_string(static_display_object->get_ID()) + " and object: " + std::to_string(static_display_objects.get_full_list()[i]->get_ID()) + '\n';
				return;
			}
		}
		static_display_objects.insert(static_display_object, static_display_object->get_draw_layer());
	}
	void Alienor::reg_main_menu_object(std::shared_ptr<Menu_Button> main_menu_object)
	{
		if (main_menu_objects.get_full_list().size() == 0)
		{
			main_menu_objects.insert(main_menu_object, main_menu_object->get_draw_layer());
			return;
		}
		for (int i = 0; i < main_menu_objects.get_full_list().size(); i++)
		{
			if (main_menu_object->get_name() == all_objects.get_full_list()[i]->get_name())
			{
				std::cout << "Name conflict: " + main_menu_object->get_name() + " between object: " + std::to_string(main_menu_object->get_ID()) + " and object: " + std::to_string(main_menu_objects.get_full_list()[i]->get_ID()) + '\n';
				return;
			}
		}
		main_menu_objects.insert(main_menu_object, main_menu_object->get_draw_layer());
	}
	void Alienor::reg_end_screen_object(std::shared_ptr<Menu_Button> end_screen_object)
	{
		if (end_screen_objects.get_full_list().size() == 0)
		{
			end_screen_objects.insert(end_screen_object, end_screen_object->get_draw_layer());
			return;
		}
		for (int i = 0; i < end_screen_objects.get_full_list().size(); i++)
		{
			if (end_screen_object->get_name() == end_screen_objects.get_full_list()[i]->get_name())
			{
				std::cout << "Name conflict: " + end_screen_object->get_name() + " between object: " + std::to_string(end_screen_object->get_ID()) + " and object: " + std::to_string(end_screen_objects.get_full_list()[i]->get_ID()) + '\n';
				return;
			}
		}
		end_screen_objects.insert(end_screen_object, end_screen_object->get_draw_layer());
	}

	//private functions for file cleanliness
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
			bool ender_collided = false;
			for (int i = 0; i < all_enders.size(); i++)
			{
				for (int j = 0; j < all_game_actors.size(); j++)
				{
					if (all_enders[i]->get_quad()->is_intersecting(all_game_actors[j]->get_quad()))
					{
#if _DEBUG & COLLISION_DEBUG_INFORMATION
						std::cout << "ender collided\n";
#endif // _DEBUG
						reset_game();
						ender_collided = true;
						break;
					}
				}
				if (ender_collided)
					break;
			}

			//boosters collision
			bool booster_collided = false;
			for (int i = 0; i < all_boosters.size(); i++)
			{
				for (int j = 0; j < all_game_actors.size(); j++)
				{
					if (all_game_actors[j]->on_a_booster)
						score++;
					if (all_boosters[i]->get_quad()->is_intersecting(all_game_actors[j]->get_quad()))
					{
#if _DEBUG & COLLISION_DEBUG_INFORMATION
						std::cout << "booster collided\n";
#endif // _DEBUG
						all_game_actors[j]->on_a_booster = true;
						booster_collided = true;
						break;
					}
					else 
					{
						all_game_actors[j]->on_a_booster = false;
					}
				}
				if (booster_collided)
					break;
			}

		}

	void Alienor::spawn_boosters_and_enders()
	{
		if (glfwGetTime() - last_spawn_time_booster >= next_spawn_interval_booster)
		{
			make_booster();
			next_spawn_interval_booster = spawn_time_distribution_booster(mersenne_rng);
			last_spawn_time_booster = glfwGetTime();
		}
		if (glfwGetTime() - last_spawn_time_ender >= next_spawn_interval_ender)
		{
			make_ender();
			next_spawn_interval_ender = spawn_time_distribution_ender(mersenne_rng);
			last_spawn_time_ender = glfwGetTime();
		}

	}
	void Alienor::clean_boosters_and_enders()
	{
		for (int i = 0; i < all_boosters.size(); i++)
		{
			if (all_boosters[i]->is_marked_for_death())
			{
#if _DEBUG & ERASURE_DEBUG_INFORMATION
				std::cout << all_boosters[i]->get_name() + " deleted\n";
#endif // _DEBUG
				all_boosters.erase(all_boosters.begin() + i);
			}
		}
		for (int i = 0; i < all_enders.size(); i++)
		{
			if (all_enders[i]->is_marked_for_death())
			{
#if _DEBUG & ERASURE_DEBUG_INFORMATION
				std::cout << all_enders[i]->get_name() + " deleted\n";
#endif // _DEBUG
				all_enders.erase(all_enders.begin() + i);
			}
		}
	}

	void Alienor::make_booster()
	{
		auto booster_temp_ptr = std::make_shared<Booster>(Booster{ pos_distribution_x(mersenne_rng), -0.5, size_distribution_booster(mersenne_rng), size_distribution_booster(mersenne_rng), 2, 0.0, vel_distribution_y_booster(mersenne_rng) });
		reg_obj(booster_temp_ptr);
		reg_booster(booster_temp_ptr);
	} 
	void Alienor::make_ender()
	{
		auto ender_temp_ptr = std::make_shared<Ender>(Ender{ pos_distribution_x(mersenne_rng), -0.5, size_distribution_ender(mersenne_rng), size_distribution_ender(mersenne_rng), 3, 0.0, vel_distribution_y_ender(mersenne_rng) });
		reg_obj(ender_temp_ptr);
		reg_ender(ender_temp_ptr);
	}

	void Alienor::reset_game()
	{
		game_state = 2;
		all_objects.clear();
		all_boosters.clear();
		all_enders.clear();

		for (int i = 0; i < all_game_actors.size(); i++)
		{
			reg_obj(all_game_actors[i]);
			all_game_actors[i]->quad.x = 0.5;
			all_game_actors[i]->quad.y = 0.75;
			all_game_actors[i]->on_a_booster = false;
		}
	}

	void Alienor::display_score_value_decimal(double x, double y)
	{
		std::vector<uint_fast64_t> popped_score = pop_decimal_digits(score);
		for (int i = 0; i < popped_score.size(); i++)
		{
			Menu_Button temp_digit_display{ "score_digit_" + i, 4, decimal_mapped_to_display_pictures[popped_score[i]], 100, 100, 0.05, 0.05, x + (0.05 * i), y, []() {} };

			temp_digit_display.draw();
		}
	}
	std::vector<uint_fast64_t> Alienor::pop_decimal_digits(const uint_fast64_t& num)
	{
		if (num == 0)
		{
			std::vector<uint_fast64_t> ret_vector;
			ret_vector.push_back(0);
			return ret_vector;
		}
		std::vector<uint_fast64_t> ret_vector;
		uint_fast64_t temp_num = num;
		uint_fast64_t temp_digit = 0;
		while (temp_num >= 1)
		{
			temp_digit = temp_num % 10;
			temp_num /= 10;
			ret_vector.push_back(temp_digit);
		}
		std::reverse(ret_vector.begin(), ret_vector.end());
		return ret_vector;
	}
}
