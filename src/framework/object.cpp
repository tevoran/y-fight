#include "y-fight.hpp"

yf::object::object(	yf::game *game,
					camera *camera,
					const char* path_to_sprite,
					const int sprite_width,
					const int sprite_height,
					const int drawing_width,
					const int drawing_height)
{
	m_camera=camera;
	m_game=game;
	SDL_Surface *tmp_surface=IMG_Load(path_to_sprite);
	if(tmp_surface==NULL)
	{
		std::cout << "[ERROR]: sprite at: \"" << path_to_sprite << "\" couldn't get loaded" << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "sprite at: \"" << path_to_sprite << "\" succesfully read" << std::endl;
	}
	texture=SDL_CreateTextureFromSurface(m_game->renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	src_rect.w=sprite_width;
	src_rect.h=sprite_height;
	dst_rect.w=drawing_width;
	dst_rect.h=drawing_height;
}

void yf::object::render(const int frame) //animations have to be in a row in an image
{
	src_rect.x=frame*src_rect.w;
	src_rect.y=0;
	dst_rect.x=x-m_camera->x;
	dst_rect.y=(m_game->resy-y)-m_camera->y; //making the bottom of the screen equal y=0
	SDL_RenderCopy(m_game->renderer, texture, &src_rect, &dst_rect);
}

void yf::object::render(const int frame, const int x, const int y) //animations have to be in a row in an image
{
	src_rect.x=frame*src_rect.w;
	src_rect.y=0;
	dst_rect.x=x-m_camera->x;
	dst_rect.y=(m_game->resy-y)-m_camera->y; //making the bottom of the screen equal y=0
	SDL_RenderCopy(m_game->renderer, texture, &src_rect, &dst_rect);
}


void yf::object::physics(const uint64_t flags)
{
	x=x+m_game->dt*x_speed;
	y=y+m_game->dt*y_speed;

	if((flags&PHYSICS_GRAVITY_FLAG) && y>=dst_rect.h)
	{
		y_speed=y_speed-m_game->dt*GRAVITY;
	}
	if(y<dst_rect.h)
	{
		y=dst_rect.h;
	}

}