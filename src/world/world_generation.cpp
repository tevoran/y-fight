#include "y-fight.hpp"


#define PATH_GATE_LEFT 0
#define PATH_GATE_TOP 1
#define PATH_GATE_RIGHT 2
#define PATH_GATE_BOTTOM 3
#define PATH_NO_EXIT 4

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

	//creating world border
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
	int room_entrance_x=rand()%(WORLD_GRID_SIZE_X-2)+1;
	int room_entrance_y=rand()%(WORLD_GRID_SIZE_Y-2)+1;
	room[room_entrance_x][room_entrance_y]=ROOM_LEVEL_ENTRANCE;
	std::cout << "entrance room is: " << room_entrance_x << "x" << room_entrance_y << std::endl;

	int entrance_x=rand()%(WORLD_GRID_SIZE-2)+1;
	entrance_x=(room_entrance_x*WORLD_GRID_SIZE)+entrance_x;
	int entrance_y=rand()%(WORLD_GRID_SIZE-6)+2;
	entrance_y=(room_entrance_y*WORLD_GRID_SIZE)+entrance_y;

	std::cout << "entrance: " << entrance_x << "x" << entrance_y << std::endl;

	PATH last_room=NONE;
	create_main_path_room(room_entrance_x, room_entrance_y, last_room);

	//randomly placing level entrance in the first room
	while(1)
	{
		exit_x=rand()%(WORLD_GRID_SIZE-2)+1;
		exit_x=(room_entrance_x*WORLD_GRID_SIZE)+entrance_x;
		exit_y=rand()%(WORLD_GRID_SIZE-4)+3;
		exit_y=(room_entrance_y*WORLD_GRID_SIZE)+entrance_y;
		//making sure that the exit is not in a wall
		if(
			world_filling[entrance_x][entrance_y]!=TILE_BORDER_WALL && 
			world_filling[entrance_x][entrance_y-1]!=TILE_BORDER_WALL)
			{
				world_filling[entrance_x][entrance_y]=TILE_ENTRANCE;
				world_filling[entrance_x][entrance_y-1]=TILE_GROUND;
				break;
			}
	}

	player.x=(entrance_x)*TILE_SIZE_X; //placing player
	player.y=(entrance_y)*(TILE_SIZE_Y);


	//creating main path
	int current_room_x=room_entrance_x;
	int current_room_y=room_entrance_y;

	for(int i=1; i<WORLD_MAIN_PATH_NUM_ROOMS; i++)
	{
		PATH next_room=(PATH)(rand()%NONE);

		switch(next_room)
		{
			case LEFT:
				if((current_room_x-1)>=0)
				{
					last_room=RIGHT;
					current_room_x--;
				}
				else
				{
					i--;
					continue;
				}
				break;
			case TOP:
				if((current_room_y+1)<WORLD_GRID_SIZE_Y)
				{
					last_room=BOTTOM;
					current_room_y++;
				}
				else
				{
					i--;
					continue;
				}
				break;
			case RIGHT:
				if((current_room_x+1)<WORLD_GRID_SIZE_X)
				{
					last_room=LEFT;
					current_room_x++;
				}
				else
				{
					i--;
					continue;
				}
				break;
			case BOTTOM:
				if((current_room_y-1)>=0)
				{
					last_room=TOP;
					current_room_y--;
				}
				else
				{
					i--;
					continue;
				}
				break;
		}
		create_main_path_room(current_room_x, current_room_y, last_room);
	}
/*
	for(int i=1; i<WORLD_MAIN_PATH_NUM_ROOMS; i++)
	{
		int next_room_direction=rand()%4;

		switch(next_room_direction)
		{
			case PATH_GATE_LEFT:
				current_room_x--;
				break;
			case PATH_GATE_TOP:
				current_room_y++;
				break;
			case PATH_GATE_RIGHT:
				current_room_x++;
				break;
			case PATH_GATE_BOTTOM:
				current_room_y--;
				break;
		}

		if(current_room_x<0)
		{
			i--;
			current_room_x++;
			continue;
		}
		if(current_room_x>=WORLD_SIZE_X)
		{
			i--;
			current_room_x--;
			continue;
		}
		if(current_room_y<0)
		{
			i--;
			current_room_y++;
			continue;
		}
		if(current_room_y>=WORLD_SIZE_Y)
		{
			i--;
			current_room_y--;
			continue;
		}

		if(room[current_room_x][current_room_y]==ROOM_MAIN_PATH)
		{
			i--;
			continue;
		}

		create_main_path_room(current_room_x, current_room_y, last_room);

		//plant level exit
		if(i==(WORLD_MAIN_PATH_NUM_ROOMS-1))
		{
			while(1)
			{
				exit_x=rand()%(WORLD_GRID_SIZE-2)+1;
				exit_x=(current_room_x*WORLD_GRID_SIZE)+exit_x;
				exit_y=rand()%(WORLD_GRID_SIZE-7)+3;
				exit_y=(current_room_y*WORLD_GRID_SIZE)+exit_y;

				//making sure that the exit is not in a wall
				if(
					world_filling[exit_x][exit_y]!=TILE_BORDER_WALL && 
					world_filling[exit_x][exit_y-1]!=TILE_BORDER_WALL)
				{
					world_filling[exit_x][exit_y]=TILE_ENTRANCE;
					world_filling[exit_x][exit_y-1]=TILE_GROUND;
					break;
				}
			}
		}
	}
*/
}

void yf::world::create_main_path_room(	const int room_x, const int room_y, const PATH last_room)
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

	//choosing type of room
	int selection=0;
	int max_selection=1;

	switch(last_room)
	{
		case LEFT:
			room_horizontal_traversal(room_x, room_y, last_room);
			break;
		case TOP:
			
			break;
		case RIGHT:
			room_horizontal_traversal(room_x, room_y, last_room);
			break;
		case BOTTOM:
			
			break;
	}
}