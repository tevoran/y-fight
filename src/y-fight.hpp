#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <chrono>

namespace yf
{

	class game
	{
	private:
		SDL_Window *window=NULL;
		SDL_Renderer *renderer=NULL;
		bool quit=false;

		std::chrono::steady_clock::time_point old_frame_time;
		std::chrono::steady_clock::time_point new_frame_time;

	public:
		int resx=0;
		int resy=0;
		float dt=0;

	public:
		game(const char* game_name);

		void update(const bool show_frame_time);
		void main_loop();
		void input_handling();
	};


}