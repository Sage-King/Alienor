#ifndef MOVE_LEFT_H_GUARD
#define MOVE_LEFT_H_GUARD
#include "Command.h"
namespace Sage
{
	class Move_Left : public Command
	{
	public:
		Move_Left() {}
		~Move_Left() {}
		void execute(const std::shared_ptr<Game_Actor>& actor, double delta_time) override
		{
			actor->move_left(delta_time);
		}
	};
}
#endif