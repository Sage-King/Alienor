#include "Ender.h"
#include <unordered_map>
#include "Alienor.h"

namespace Sage
{
	Ender::Ender(const std::string& filepath, unsigned int sprite_size_x, unsigned int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y, unsigned int draw_layer)
		:
		Collidable("ender_" + std::to_string(ID_factory++) + '_' + filepath.substr(10, filepath.length() - 14), draw_layer),
		quad(Quad{ filepath, sprite_size_x,sprite_size_y, quad_size_x,quad_size_y, quad_loc_x,quad_loc_y })
	{

	}
	Ender::Ender(double quad_loc_x, double quad_loc_y, double quad_size_x, double quad_size_y, unsigned int draw_layer, double initial_vel_x, double initial_vel_y)
		:
		Collidable("ender_" + std::to_string(ID_factory++), draw_layer),
		quad(Quad{ glm::vec4{1.0,0.0,0.0,1.0}, quad_size_x, quad_size_y, quad_loc_x, quad_loc_y }),
		vel(initial_vel_x, initial_vel_y)
	{

	}
	void Ender::draw()
	{
		quad.draw();
	}
	void Ender::update(double delta_time)
	{
		quad.y += vel.y * delta_time;
		quad.x += vel.x * delta_time;
		if (quad.y >= 1.0f)
		{
			marked_for_death = true;
		}
	}
}