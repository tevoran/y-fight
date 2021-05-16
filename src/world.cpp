#include "y-fight.hpp"

#define TILE_GROUND 0
#define TILE_BACKGROUND 1
#define TILE_BORDER_WALL 2
#define TILE_ENTRANCE 3


#define TILE_SIZE_X (int)(0.052*(float)m_game->resx)
#define TILE_SIZE_Y (int)(0.096*(float)m_game->resy)

//player gets located at the level entrance
yf::world::world(game* game, camera *camera, const char* path_to_tileset, object& player)
{
	m_game=game;
	m_camera=camera;
	world_tileset.push_back(object(m_game, camera, path_to_tileset, 16, 16, TILE_SIZE_X, TILE_SIZE_Y));


	//creating game world
	//creating background
	for(int iy=0; iy<(WORLD_SIZE_Y); iy++)
	{
		for(int ix=0; ix<WORLD_SIZE_X; ix++)
		{
			world_filling[ix][iy]=TILE_BACKGROUND;
		}
	}

	//creating border
	for(int ix=0; ix<WORLD_SIZE_X; ix++)
	{
		world_filling[ix][0]=TILE_BORDER_WALL;
		world_filling[ix][WORLD_SIZE_Y-1]=TILE_BORDER_WALL;
	}
	for(int iy=0; iy<WORLD_SIZE_Y; iy++)
	{
		world_filling[0][iy]=TILE_BORDER_WALL;
		world_filling[WORLD_SIZE_X-1][iy]=TILE_BORDER_WALL;
	}

	//creating level entrance
	int entrance_x=rand()%(WORLD_SIZE_X-2)+1;
	int entrance_y=rand()%(WORLD_SIZE_Y-6)+2;

	world_filling[entrance_x][entrance_y+1]=TILE_ENTRANCE;
	world_filling[entrance_x][entrance_y]=TILE_GROUND;

	player.x=entrance_x*TILE_SIZE_X;
	player.y=(entrance_y*(TILE_SIZE_Y)-3);


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

	int player_tile_x=(int)(player.x/TILE_SIZE_X+0.5);
	int player_tile_y=(int)(player.y/TILE_SIZE_Y+0.5);

	//collision with border walls
	//checking right side
	if(player_tile_x<WORLD_SIZE_X-1) //avoiding segfaults
	{
		if(world_filling[player_tile_x+1][player_tile_y]==TILE_BORDER_WALL)
		{
			world_collision.x=(player_tile_x+1)*TILE_SIZE_X-m_camera->x;
			world_collision.y=(m_game->resy-(player_tile_y)*TILE_SIZE_Y)-m_camera->y;
			if(collision(player.dst_rect, world_collision))
			{
				player.x=(player_tile_x+1)*TILE_SIZE_X-player.dst_rect.w;
				player.x_speed=0;
			}
		}
	}

	//checking left side
	if(player_tile_x>0) //avoiding segfaults
	{
		if(world_filling[player_tile_x-1][player_tile_y]==TILE_BORDER_WALL)
		{
			world_collision.x=(player_tile_x-1)*TILE_SIZE_X-m_camera->x;
			world_collision.y=(m_game->resy-(player_tile_y)*TILE_SIZE_Y)-m_camera->y;
			if(collision(player.dst_rect, world_collision))
			{
				player.x=(player_tile_x)*TILE_SIZE_X;
				player.x_speed=0;
			}
		}
	}

	//checking top side
	if(player_tile_y<WORLD_SIZE_Y-1) //avoiding segfaults
	{
		if(world_filling[player_tile_x][player_tile_y+1]==TILE_BORDER_WALL)
		{
			world_collision.x=(player_tile_x)*TILE_SIZE_X-m_camera->x;
			world_collision.y=(m_game->resy-(player_tile_y+1)*TILE_SIZE_Y)-m_camera->y;
			if(collision(player.dst_rect, world_collision))
			{
				player.y=(player_tile_y)*TILE_SIZE_Y;
				player.y_speed=0;
			}
		}
	}

	//checking bottom side
	if(player_tile_y>0) //avoiding segfaults
	{
		if(world_filling[player_tile_x][player_tile_y-1]==TILE_BORDER_WALL)
		{
			world_collision.x=(player_tile_x)*TILE_SIZE_X-m_camera->x;
			world_collision.y=(m_game->resy-(player_tile_y-1)*TILE_SIZE_Y)-m_camera->y;
			if(collision(player.dst_rect, world_collision))
			{
				player.y=(player_tile_y-1)*TILE_SIZE_Y+player.dst_rect.h-1;
				player.y_speed=0;
				player.standing=true;
				player.x_speed=0.9*player.x_speed;				
			}
		}
	}


	//collision with ground tiles
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
					//player is on top of a ground tile
					if(player.y_speed<0)
					{
						player.y=iy*TILE_SIZE_Y+player.dst_rect.h-1;
						player.y_speed=0;
						player.standing=true;
						player.x_speed=0.9*player.x_speed;
					}
				}
			}
		}
	}
}