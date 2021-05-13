#include "y-fight.hpp"

#define PLAYER_X_SPEED 0.17
#define PLAYER_Y_SPEED 1.1

bool double_jump=true;
float double_jump_cooldown=0.1;

void yf::input_handling(game& game, object& player)
{
	//cooldowns
	double_jump_cooldown-=game.dt;
	if(double_jump_cooldown<0)
	{
		double_jump_cooldown=0;
	}

	SDL_Event event;
	while(SDL_PollEvent(&event))
	{

	}
	const Uint8 *keyboard_state=SDL_GetKeyboardState(NULL);
	if(keyboard_state[SDL_SCANCODE_ESCAPE])
	{
		game.quit=true;
	}

	//player movement
	//X-Axis
	if(keyboard_state[SDL_SCANCODE_D])
	{
		player.x_speed=PLAYER_X_SPEED*(float)game.resx;
	}
	if(keyboard_state[SDL_SCANCODE_A])
	{
		player.x_speed=-PLAYER_X_SPEED*(float)game.resx;
	}
	if(keyboard_state[SDL_SCANCODE_D] && keyboard_state[SDL_SCANCODE_A])
	{
		player.x_speed=0;
	}

	//Y-Axis
	if(keyboard_state[SDL_SCANCODE_SPACE] && double_jump==true && double_jump_cooldown==0) //second jump
	{
		player.y_speed=1.2*PLAYER_Y_SPEED*(float)game.resy;
		double_jump=false;
	}
	if(keyboard_state[SDL_SCANCODE_SPACE] && player.y==player.dst_rect.h) //first jump
	{
		player.y_speed=PLAYER_Y_SPEED*(float)game.resy;
		double_jump=true;
		double_jump_cooldown=DOUBLE_JUMP_COOLDOWN;
	}
}