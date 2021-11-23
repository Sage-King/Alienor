#ifndef ALIENOR_H_GUARD
#define ALIENOR_H_GUARD
#include <glm/glm.hpp>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Object.h>
#include <unordered_map>
#include <Collidable.h>
#include <Booster.h>
#include "Ender.h"
#include <Input_Handler.h>
#include "Player.h"
#include "Bucket_Vector.h"
#include "Menu_Button.h"
#include <random>
#include <iterator>

namespace Sage
{
	class Alienor
	{
	public:
		Alienor(GLFWwindow* window);

		void update();
		void draw();

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		//these should probably be templates, but outside of the scope of the this project
		//(I don't know exactly how and I've deemed it to expensive to find out) - 11/20/2021
		void reg_obj(std::shared_ptr<Object> obj);
		void reg_booster(std::shared_ptr<Booster> booster);
		void reg_ender(std::shared_ptr<Ender> ender);
		void reg_menu_object(std::shared_ptr<Menu_Button> menu_button);
		void reg_game_actor(std::shared_ptr<Game_Actor> game_actor);

		double get_delta_time() { return delta_time; }
		const std::vector<std::shared_ptr<Object>>& get_all_objects(){return all_objects.get_full_list();}

		inline bool get_valid_exit() { return valid_exit; }
		inline void set_valid_exit(bool val) { valid_exit = val; }

		inline unsigned int get_game_state() { return game_state; }
	private:
		void process_inputs();
		void process_collisions();

		double delta_time;
		double last_frame = 0.0f;

		unsigned int game_state = 0;
		//0 is main menu
		//1 is game
		//anything else is invalid
		bool valid_exit = true;
		 
		Bucket_Vector<std::shared_ptr<Object>> all_objects{ 5 /*num of draw layers*/};
		std::vector<std::shared_ptr<Booster>> all_boosters;
		std::vector<std::shared_ptr<Ender>> all_enders;
		std::vector<std::shared_ptr<Game_Actor>> all_game_actors;

		Bucket_Vector<std::shared_ptr<Menu_Button>> all_menu_buttons{ 5 /*num of draw layers*/};
		Input_Handler input_handler;

		std::random_device rand_device;
		std::mt19937 rng;
		std::uniform_real_distribution<float> pos_distribution;

		glm::vec4 background_color;
		GLFWwindow* window;
	};
}
#endif