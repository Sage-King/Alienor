#ifndef OBSTACLE_H_GUARD
#define OBSTACLE_H_GUARD
#include "Quad.h"
#include "Game_Actor.h"
namespace Sage
{
	class Obstacle : public Collidable
	{
	public:
		Obstacle(const std::string& filepath, int sprite_size_x, int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y);

		void update() override;
		void draw() override;
		std::pair<bool, Quad> is_quad() override
		{
			return std::pair<bool, Quad>{true, quad};
		}
		void set_sprite_x(int sprite_x) { quad.sprite_number_x = sprite_x; }
		int get_sprite_x() { return quad.sprite_number_x; }
	private:
		inline static int ID_factory = 0;
		Quad quad;
	};
}
#endif