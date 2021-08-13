#ifndef ALIENOR_H_GUARD
#define ALIENOR_H_GUARD
#include <glm/glm.hpp>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Object.h>
#include <unordered_map>
#include <Collidable.h>
#include <Input_Handler.h>

namespace Sage
{
	class Alienor
	{
	public:
		Alienor(GLFWwindow* window);

		void update();
		void draw();

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void reg_obj(std::shared_ptr<Object> obj);
		void reg_collidable(std::shared_ptr<Collidable> collidable);
		void reg_game_actor(std::shared_ptr<Game_Actor> game_actor);

		double get_delta_time() { return delta_time; }
		const std::vector<std::shared_ptr<Object>>& get_all_objects(){return all_objects;}
		const std::vector<std::shared_ptr<Collidable>>& get_all_collidables(){return all_collidables;}
	private:
		void process_inputs();
		void process_collisions();

		double delta_time;
		double last_frame = 0.0f;

		std::vector<std::shared_ptr<Object>> all_objects;
		std::vector<std::shared_ptr<Collidable>> all_collidables;
		std::vector<std::shared_ptr<Game_Actor>> all_game_actors;

		Input_Handler i_handler;

		glm::vec4 background_color;
	};
}
#endif