#ifndef ENDER_H_GUARD
#define ENDER_H_GUARD
#include "Quad.h"
#include "Game_Actor.h"
#include <glm/glm.hpp>
#include "Vel_Struct.h"
namespace Sage
{
	class Ender : public Collidable
	{
	public:
		Ender(const std::string& filepath, unsigned int sprite_size_x, unsigned int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y, unsigned int draw_layer, double initial_vel_x, double initial_vel_y);
		Ender(double quad_loc_x, double quad_loc_y, double quad_size_x, double quad_size_y, unsigned int draw_layer, double initial_vel_x, double initial_vel_y);

		void update(double delta_time) override;
		void draw() override;
		const Quad* get_quad()
		{
			return &quad;
		}
		void set_sprite_x(int sprite_x) { quad.sprite_number_x = sprite_x; }
		int get_sprite_x() { return quad.sprite_number_x; }
		bool is_marked_for_death() { return marked_for_death; }
	private:
		inline static int ID_factory = 0;
		Quad quad;
		bool marked_for_death = false;

		Vel vel{ 0.0, 0.0 };
	};
}
#endif