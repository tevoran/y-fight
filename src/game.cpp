#include "y-fight.hpp"


yf::game::game(const char* game_name)
{
	std::cout << "initializing game...";

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	SDL_DisplayMode mode_info;
	if(SDL_GetDesktopDisplayMode(0, &mode_info)!=0)
	{
		std::cout << std::endl << "[WARNING]: Couldn't get desktop resolution" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(0);
	}

	resx=mode_info.w;
	resy=mode_info.h;

	window=SDL_CreateWindow(game_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resx, resy, SDL_WINDOW_FULLSCREEN);
	if(window==NULL)
	{
		std::cout << std::endl << "SDL can't create a window" << std::endl;
		exit(0);
	}

	renderer=SDL_CreateRenderer(window, -1, 0);
	if(renderer==NULL)
	{
		std::cout << std::endl << "SDL can't create a renderer" << std::endl;
		exit(0);
	}

	std::cout << "done" << std::endl;
}

void yf::game::update(const bool show_frame_time)
{
	//get current frame_time
	old_frame_time=new_frame_time;
	new_frame_time=std::chrono::steady_clock::now();
	std::chrono::duration<float> dt_chrono=std::chrono::duration_cast<std::chrono::duration<float>>(new_frame_time-old_frame_time);
	dt=dt_chrono.count();
	if(show_frame_time)
	{
		std::cout << "frame_time: " << dt << "s" << std::endl;
	}

	//rendering
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 187, 255, 0); //Skylike color
	SDL_RenderClear(renderer);
}
