#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>


#define DOUBLE_JUMP_COOLDOWN 0.15
#define DASH_SPEED 1.4*1.77*game.resy
#define DASH_DURATION 0.3
#define DASH_COOLDOWN DASH_DURATION+1
#define WORLD_SIZE_X 100
#define WORLD_SIZE_Y 25
#define GRAVITY 1.7*(float)m_game->resy

#define PHYSICS_GRAVITY_FLAG 0x01

namespace yf
{
	class camera
	{
	private:
		float *past_frame_x=NULL;
		float *past_frame_y=NULL;
		float camera_new_frame_cooldown=0;
		int num_delayed_frames=0;
		int m_resx=0;
		int m_resy=0;
		int m_player_height=0;
	public:
		float x=0;
		float y=0;
		camera(float delay, int resx, int resy, int player_height);
		~camera();
		void update(float frame_dt, float player_x, float player_y);
	};

	class game
	{
	private:
		SDL_Window *window=NULL;

		std::chrono::steady_clock::time_point old_frame_time;
		std::chrono::steady_clock::time_point new_frame_time;

	public:
		TTF_Font *font=NULL;
		bool quit=false;
		SDL_Renderer *renderer=NULL;
		int resx=0;
		int resy=0;
		int mousex=0;
		int mousey=0;
		float dt=0;

	public:
		game(const char* game_name);

		void update(const bool show_frame_time, camera& camera);
	};


	class object
	{
	private:
		SDL_Rect src_rect;
		SDL_Texture *texture=NULL;
		game *m_game=NULL;
		camera *m_camera=NULL;
	public:
		SDL_Rect dst_rect;
		float x=0;
		float y=0;
		float x_speed=0;
		float y_speed=0;

	public:		
		object(	yf::game *game,
				camera *camera,
				const char* path_to_sprite,
				const int sprite_width,
				const int sprite_height,
				const int drawing_width,
				const int drawing_height);
		void render(const int frame);
		void render(const int frame, const int x, const int y);
		void physics(const uint64_t flags);
	};

	class world
	{
	private:
		std::vector<object> world_tileset;
		game *m_game=NULL;
		int world_filling[WORLD_SIZE_X][WORLD_SIZE_Y];
	public:
		world(game* game, camera *camera, const char* path_to_tileset);
		void render();
	};

	void input_handling(game& game, camera& camera, object& player, object& cursor);
}