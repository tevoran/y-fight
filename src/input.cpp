#include "y-fight.hpp"

void yf::game::input_handling()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{

	}
	const Uint8 *keyboard_state=SDL_GetKeyboardState(NULL);
	if(keyboard_state[SDL_SCANCODE_ESCAPE])
	{
		quit=true;
	}
}