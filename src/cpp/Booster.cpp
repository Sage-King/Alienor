#include "Booster.h"
#include <unordered_map>
#include "Alienor.h"

namespace Sage
{
	Booster::Booster(const std::string& filepath, unsigned int sprite_size_x, unsigned int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y, unsigned int draw_layer, double initial_speed_x, double initial_speed_y)
		:
		Collidable("booster_" + std::to_string(ID_factory++) + '_' + filepath, draw_layer),
		quad(Quad{ filepath, sprite_size_x, sprite_size_y, quad_size_x, quad_size_y, quad_loc_x, quad_loc_y }),
		vel(initial_speed_x, initial_speed_y)
	{

	}
	Booster::Booster(double quad_loc_x, double quad_loc_y, double quad_size_x, double quad_size_y, unsigned int draw_layer, double initial_speed_x, double initial_speed_y)
		:
		Collidable("booster_" + std::to_string(ID_factory++), draw_layer),
		quad(Quad{ glm::vec4{0.568,0.71,1.0,1.0}, quad_size_x, quad_size_y, quad_loc_x, quad_loc_y }),
		vel(initial_speed_x, initial_speed_y)
	{

	}
	void Booster::draw()
	{
		quad.draw();
	}
	void Booster::update(double delta_time)
	{
		quad.y += vel.y * delta_time;
		quad.x += vel.x * delta_time;
		if (quad.y >= 1.0f)
		{
			marked_for_death = true;
		}
	}
}