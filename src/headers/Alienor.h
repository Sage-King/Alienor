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
		void reg_main_menu_object(std::shared_ptr<Menu_Button>	main_menu_object);
		void reg_end_screen_object(std::shared_ptr<Menu_Button> end_screen_object);
		void reg_game_actor(std::shared_ptr<Game_Actor> game_actor);
		void reg_static_display_object(std::shared_ptr<Menu_Button> static_display_object);

		double get_delta_time() { return delta_time; }
		const std::vector<std::shared_ptr<Object>>& get_all_objects(){return all_objects.get_full_list();}

		inline bool get_valid_exit() { return valid_exit; }
		inline void set_valid_exit(bool val) { valid_exit = val; }

		inline unsigned int get_game_state() { return game_state; }
	private:
		void process_inputs();
		void process_collisions();
		void clean_boosters_and_enders();
		void spawn_boosters_and_enders();
		void make_booster();
		void make_ender();
		void reset_game();

		void display_score_value_decimal(double x, double y);
		std::vector<uint_fast64_t> pop_decimal_digits(const uint_fast64_t& num);

		double delta_time;
		double last_frame = 0.0f;

		unsigned int game_state = 0;
		//0 is main menu
		//1 is game
		//2 is end screen
		//anything else is invalid

		bool valid_exit = true;
		 
		Bucket_Vector<std::shared_ptr<Object>> all_objects{ 5 /*num of draw layers*/}; //probably closer to all_in_game_objects because the menu buttons aren't handled here.  (They don't have update functions and will throw tons of errors if they're put in the all_objects vector)
		std::vector<std::shared_ptr<Booster>> all_boosters;
		std::vector<std::shared_ptr<Ender>> all_enders;

		//this vector has caused so many problems and I'm just too deep to want to fix it
		//I think I'd rather have it just be a Player variable for simplicity, but this allows expansion I guess
		std::vector<std::shared_ptr<Game_Actor>> all_game_actors;

		Bucket_Vector<std::shared_ptr<Menu_Button>> main_menu_objects{ 5 /*num of draw layers*/};
		Bucket_Vector<std::shared_ptr<Menu_Button>> end_screen_objects{ 5 /*num of draw layers*/};
		Bucket_Vector<std::shared_ptr<Menu_Button>> static_display_objects{ 5 /*num of draw layers*/};

		Input_Handler input_handler;

		std::random_device rand_device;
		std::mt19937 mersenne_rng;
		std::uniform_real_distribution<float> pos_distribution_x, vel_distribution_y_booster, vel_distribution_y_ender, spawn_time_distribution_booster, spawn_time_distribution_ender, size_distribution_booster, size_distribution_ender;

		double last_spawn_time_booster = 0.0;
		double last_spawn_time_ender = 0.0;
		double next_spawn_interval_booster = 0.0;
		double next_spawn_interval_ender = 0.0;

		uint_fast64_t score = 0;

		glm::vec4 game_background_color, main_menu_background_color, end_screen_background_color;
		GLFWwindow* window;

		const std::vector<std::string> decimal_mapped_to_display_pictures = {
			"resources\\zero.png",
			"resources\\one.png",
			"resources\\two.png",
			"resources\\three.png",
			"resources\\four.png",
			"resources\\five.png",
			"resources\\six.png",
			"resources\\seven.png",
			"resources\\eight.png",
			"resources\\nine.png",
		};
	};
}
#endif