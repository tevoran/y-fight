#include "y-fight.hpp"

#define TILE_GROUND 0
#define TILE_BACKGROUND 1
#define TILE_BORDER_WALL 2
#define TILE_ENTRANCE 3

#define TILE_SIZE_X (int)(0.052*(float)m_game->resx)
#define TILE_SIZE_Y (int)(0.096*(float)m_game->resy)

#define ROOM_EMPTY 0
#define ROOM_LEVEL_ENTRANCE 1
#define ROOM_MAIN_PATH 2

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

	//creating level border
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

	//creating rooms
	for(int iy=0; iy<WORLD_GRID_SIZE_Y; iy++)
	{
		for(int ix=0; ix<WORLD_GRID_SIZE_X; ix++)
		{
			room[ix][iy]=ROOM_EMPTY;
		}
	}

	//creating level entrance room
	int room_entrance_x=rand()%(WORLD_GRID_SIZE_X-1);
	int room_entrance_y=rand()%(WORLD_GRID_SIZE_Y-1);
	room[room_entrance_x][room_entrance_y]=ROOM_LEVEL_ENTRANCE;
	std::cout << "entrance room is: " << room_entrance_x << "x" << room_entrance_y << std::endl;

	int entrance_x=rand()%(WORLD_GRID_SIZE-2)+1;
	entrance_x=(room_entrance_x*WORLD_GRID_SIZE)+entrance_x;
	int entrance_y=rand()%(WORLD_GRID_SIZE-6)+2;
	entrance_y=(room_entrance_y*WORLD_GRID_SIZE)+entrance_y;

	std::cout << "entrance: " << entrance_x << "x" << entrance_y << std::endl;

	world_filling[entrance_x][entrance_y+1]=TILE_ENTRANCE;
	world_filling[entrance_x][entrance_y]=TILE_GROUND;

	create_main_path_room(room_entrance_x, room_entrance_y, false, false, false, false);
	player.x=(entrance_x)*TILE_SIZE_X;
	player.y=(entrance_y*(TILE_SIZE_Y));


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
		if(	world_filling[player_tile_x+1][player_tile_y]==TILE_BORDER_WALL)
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
		if(	world_filling[player_tile_x-1][player_tile_y]==TILE_BORDER_WALL)
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
		if(	world_filling[player_tile_x][player_tile_y+1]==TILE_BORDER_WALL)
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
		if(	world_filling[player_tile_x][player_tile_y-1]==TILE_BORDER_WALL)
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

/*	//collision with ground tiles
	//checking right side
	if(player_tile_x<WORLD_SIZE_X-1) //avoiding segfaults
	{
		if(world_filling[player_tile_x+1][player_tile_y]==TILE_GROUND)
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
		if(world_filling[player_tile_x-1][player_tile_y]==TILE_GROUND)
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
		if(world_filling[player_tile_x][player_tile_y+1]==TILE_GROUND)
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
		if(world_filling[player_tile_x][player_tile_y-1]==TILE_GROUND)
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
	}*/

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

void yf::world::create_main_path_room(	const int room_x, 
									const int room_y, 
									const bool gate_left, 
									const bool gate_top, 
									const bool gate_right, 
									const bool gate_bottom)
{
	room[room_x][room_y]=ROOM_MAIN_PATH;

	//making room border
	//floor
	for(int i=0; i<WORLD_GRID_SIZE; i++)
	{
		world_filling[room_x*WORLD_GRID_SIZE+i][room_y*WORLD_GRID_SIZE]=TILE_BORDER_WALL;
	}
	//ceiling
	for(int i=0; i<WORLD_GRID_SIZE; i++)
	{
		world_filling[room_x*WORLD_GRID_SIZE+i][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1]=TILE_BORDER_WALL;
	}
	//left wall
	for(int i=0; i<WORLD_GRID_SIZE; i++)
	{
		world_filling[room_x*WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+i]=TILE_BORDER_WALL;
	}
	//right wall
	for(int i=0; i<WORLD_GRID_SIZE; i++)
	{
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+i]=TILE_BORDER_WALL;
	}

	//creating random ground segments
	int num_floor_segments=rand()%WORLD_MAX_FLOOR_SEGMENTS;
	for(int i=0; i<num_floor_segments; i++)
	{
		int location_x=rand()%(WORLD_GRID_SIZE-2)+1;
		int location_y=rand()%(WORLD_GRID_SIZE-2);
		int seg_length=rand()%(WORLD_GRID_SIZE/2);

		for(int i=0; i<seg_length; i++)
		{
			if(world_filling[room_x*WORLD_GRID_SIZE+location_x+i][room_y*WORLD_GRID_SIZE+location_y]==TILE_ENTRANCE)
			{
				continue;
			}

			world_filling[room_x*WORLD_GRID_SIZE+location_x+i][room_y*WORLD_GRID_SIZE+location_y]=TILE_GROUND;
			if((location_x+i)>=(WORLD_GRID_SIZE-2))
			{
				break;
			}
		}

	}
}