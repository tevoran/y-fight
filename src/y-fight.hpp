#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace yf
{

	class game
	{
	private:
		SDL_Window *window=NULL;
		SDL_Renderer *renderer=NULL;
		bool quit=false;

	public:
		int resx=0;
		int resy=0;

	public:
		game(const char* game_name);

		void update();
		void main_loop();
	};
}