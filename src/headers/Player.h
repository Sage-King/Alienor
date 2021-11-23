#ifndef PLAYER_H_GUARD
#define PLAYER_H_GUARD
#include "Texture.h"
#include "Quad.h"
#include "Game_Actor.h"
namespace Sage 
{
	class Player : public Game_Actor
	{
	public:
		Player();
		~Player();

		void move_up(double delta_time) override;
		void move_down(double delta_time) override;
		void move_right(double delta_time) override;
		void move_left(double delta_time) override;

		void draw() override;
		void update(double delta_time) override;
	private:

		double last_change = 0.0;

	};
}
#endif