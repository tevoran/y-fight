#include "y-fight.hpp"

#define TILE_GROUND 0
#define TILE_BACKGROUND 1


#define TILE_SIZE_X (int)(0.052*(float)m_game->resx)
#define TILE_SIZE_Y (int)(0.096*(float)m_game->resy)

yf::world::world(game* game, camera *camera, const char* path_to_tileset)
{
	m_game=game;
	m_camera=camera;
	world_tileset.push_back(object(m_game, camera, path_to_tileset, 16, 16, TILE_SIZE_X, TILE_SIZE_Y));


	//creating game world
	for(int iy=0; iy<(WORLD_SIZE_Y); iy++)
	{
		for(int ix=0; ix<WORLD_SIZE_X; ix++)
		{
			world_filling[ix][iy]=TILE_BACKGROUND;
			if(iy==0)
			{
				world_filling[ix][iy]=TILE_GROUND;
			}
			if(iy%10==0)
			{
				world_filling[ix][iy]=TILE_GROUND;
			}
		}
	}
}

void yf::world::render()
{
	for(int iy=0; iy<(WORLD_SIZE_Y); iy++)
	{
		if(	((m_game->resy-(iy-1)*TILE_SIZE_Y)-m_camera->y)>0 && 
			((m_game->resy-iy*TILE_SIZE_Y)-m_camera->y)<m_game->resy)
		{
			for(int ix=0; ix<WORLD_SIZE_X; ix++)
			{
				world_tileset[0].render(world_filling[ix][iy], ix*TILE_SIZE_X, iy*TILE_SIZE_Y);
			}			
		}

	}
}

void yf::world::interact(object& player)
{
	SDL_Rect world_collision;
	world_collision.w=TILE_SIZE_X;
	world_collision.h=TILE_SIZE_Y;

	for(int iy=0; iy<WORLD_SIZE_Y; iy++)
	{
		for(int ix=0; ix<WORLD_SIZE_X; ix++)
		{
			//checking for collision with a ground tile
			if(world_filling[ix][iy]==TILE_GROUND)
			{
				world_collision.x=ix*TILE_SIZE_X-m_camera->x;
				world_collision.y=(m_game->resy-iy*TILE_SIZE_Y)-m_camera->y;
				if(collision(player.dst_rect, world_collision))
				{
					//player is on top
					if(player.y_speed<0)
					{
						player.y=iy*TILE_SIZE_Y+player.dst_rect.h-1;
						player.y_speed=0;
						player.standing=true;
					}
				}
			}
		}
	}
}