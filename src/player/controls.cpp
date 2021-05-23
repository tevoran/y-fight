#include "y-fight.hpp"

#define PLAYER_X_SPEED 0.25
#define PLAYER_Y_SPEED 1

bool double_jump=true;
float double_jump_cooldown=0.1;

float dash_x=0;
float dash_y=0;
float dash_still_active=0;
float dash_cooldown=0;

void yf::input_handling(game& game, camera& camera, object& player, object& cursor)
{
	//dash
	dash_cooldown-=game.dt;
	if(dash_cooldown<0)
	{
		dash_cooldown=0;
	}
	if(dash_still_active>0)
	{
		player.x_speed=DASH_SPEED*dash_x;
		player.y_speed=DASH_SPEED*dash_y;
		dash_still_active-=game.dt;
		if(dash_still_active<=0)
		{
			player.x_speed=AFTER_DASH_SPEED*player.x_speed;
			player.y_speed=AFTER_DASH_SPEED*player.y_speed;
		}
	}

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

	SDL_GetMouseState(&game.mousex, &game.mousey);
	game.mousey=game.resy-game.mousey; //accommodating screen coordinates
	cursor.x=game.mousex+camera.x;
	cursor.y=game.mousey-camera.y;


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
	if(!keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
	{
		//player.x_speed=0;
	}

	//Y-Axis
	if(keyboard_state[SDL_SCANCODE_SPACE] && double_jump==true && double_jump_cooldown==0) //second jump
	{
		player.y_speed=PLAYER_Y_SPEED*(float)game.resy;
		double_jump=false;
	}
	if(keyboard_state[SDL_SCANCODE_SPACE] && player.standing==true) //first jump
	{
		player.y_speed=PLAYER_Y_SPEED*(float)game.resy;
		player.standing=false;
		double_jump=true;
		double_jump_cooldown=DOUBLE_JUMP_COOLDOWN;
	}

	//activating dash
	if(keyboard_state[SDL_SCANCODE_LALT] && dash_cooldown==0)
	{
		dash_x=cursor.x-player.x;
		dash_y=cursor.y-player.y;
		float normalize_sum=sqrt(dash_x*dash_x+dash_y*dash_y);
		dash_x=dash_x/normalize_sum;
		dash_y=dash_y/normalize_sum;
		dash_still_active=DASH_DURATION;
		dash_cooldown=DASH_COOLDOWN;
	}
}