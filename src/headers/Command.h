#ifndef COMMAND_H_GUARD
#define COMMAND_H_GUARD
#include "Game_Actor.h"
namespace Sage
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(const std::shared_ptr<Game_Actor>& actor, double delta_time) { std::cout << "Command Base Called\n"; }
	};
}
#endif