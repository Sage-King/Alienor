#ifndef MOVE_UP_H_GUARD
#define MOVE_UP_H_GUARD
#include "Command.h"
namespace Sage
{
	class Move_Up : public Command
	{
	public:
		Move_Up() {}
		~Move_Up() {}
		void execute(const std::shared_ptr<Game_Actor>& actor, double delta_time) override
		{
			actor->move_up(delta_time);
		}
	};
}
#endif