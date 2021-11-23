#ifndef GAME_ACTOR_H_GUARD
#define GAME_ACTOR_H_GUARD
#include "Collidable.h"
namespace Sage
{
	class Game_Actor : public Collidable
	{
	public:
		Game_Actor(const std::string& name, unsigned int draw_layer, Quad quad)
			:Collidable(name, draw_layer),
			quad(quad)
		{

		}

		virtual void move_up(double delta_time) { std::cout << "No move_up() is defined for Game_Actor: " << this->get_name() << '\n'; }
		virtual void move_down(double delta_time) { std::cout << "No move_down() is defined for Game_Actor: " << this->get_name() << '\n'; }
		virtual void move_left(double delta_time) { std::cout << "No move_left() is defined for Game_Actor: " << this->get_name() << '\n'; }
		virtual void move_right(double delta_time) { std::cout << "No move_right() is defined for Game_Actor: " << this->get_name() << '\n'; }

		const Quad* get_quad()
		{
			return &quad;
		}
		Quad quad;
	};

}
#endif