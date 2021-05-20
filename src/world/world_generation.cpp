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
	int room_entrance_x=rand()%(WORLD_GRID_SIZE_X-2)+1;
	int room_entrance_y=rand()%(WORLD_GRID_SIZE_Y-2)+1;
	room[room_entrance_x][room_entrance_y]=ROOM_LEVEL_ENTRANCE;
	std::cout << "entrance room is: " << room_entrance_x << "x" << room_entrance_y << std::endl;

	int entrance_x=rand()%(WORLD_GRID_SIZE-2)+1;
	entrance_x=(room_entrance_x*WORLD_GRID_SIZE)+entrance_x;
	int entrance_y=rand()%(WORLD_GRID_SIZE-6)+2;
	entrance_y=(room_entrance_y*WORLD_GRID_SIZE)+entrance_y;

	std::cout << "entrance: " << entrance_x << "x" << entrance_y << std::endl;

	world_filling[entrance_x][entrance_y+1]=TILE_ENTRANCE;
	world_filling[entrance_x][entrance_y]=TILE_GROUND;

	player.x=(entrance_x)*TILE_SIZE_X; //placing player
	player.y=(entrance_y+1)*(TILE_SIZE_Y);


	int gate_exit=rand()%4;
	int gate_entrance;
	if(gate_exit>=2)
	{
		gate_entrance=gate_exit-2;
	}
	else
	{
		gate_entrance=gate_exit+2;
	}

	create_main_path_room(room_entrance_x, room_entrance_y, gate_entrance, PATH_NO_EXIT);

	//creating main path
	int current_room_x=room_entrance_x;
	int current_room_y=room_entrance_y;

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

		create_main_path_room(current_room_x, current_room_y, gate_entrance, gate_exit);
	}

}

void yf::world::create_main_path_room(	const int room_x, 
										const int room_y, 
										const int gate_entrance,
										const int gate_exit)
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

	//creating entrance/exit
	if(room[room_x-1][room_y]==ROOM_MAIN_PATH && room_x>0) //left
	{
		//current room
		world_filling[room_x*WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+2]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+3]=TILE_BACKGROUND;

		//adjacent room
		world_filling[room_x*WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+2]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+3]=TILE_BACKGROUND;
	}
	if(room[room_x][room_y+1]==ROOM_MAIN_PATH && room_y<(WORLD_GRID_SIZE_Y-1)) //top
	{
		//current room
		world_filling[room_x*WORLD_GRID_SIZE+1][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+2][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+3][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1]=TILE_BACKGROUND;

		//adjacent room
		world_filling[room_x*WORLD_GRID_SIZE+1][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+2][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+3][room_y*WORLD_GRID_SIZE+WORLD_GRID_SIZE]=TILE_BACKGROUND;
	}
	if(room[room_x+1][room_y]==ROOM_MAIN_PATH && room_x<(WORLD_GRID_SIZE_X-1)) //right
	{
		//current room
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+2]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE-1][room_y*WORLD_GRID_SIZE+3]=TILE_BACKGROUND;

		//adjacent room
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+2]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+WORLD_GRID_SIZE][room_y*WORLD_GRID_SIZE+3]=TILE_BACKGROUND;
	}
	if(room[room_x][room_y-1]==ROOM_MAIN_PATH && room_y>0) //bottom
	{
		//current room
		world_filling[room_x*WORLD_GRID_SIZE+1][room_y*WORLD_GRID_SIZE]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+2][room_y*WORLD_GRID_SIZE]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+3][room_y*WORLD_GRID_SIZE]=TILE_BACKGROUND;

		//adjacent room
		world_filling[room_x*WORLD_GRID_SIZE+1][room_y*WORLD_GRID_SIZE-1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+2][room_y*WORLD_GRID_SIZE-1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+3][room_y*WORLD_GRID_SIZE-1]=TILE_BACKGROUND;
	}



	//creating random ground segments
	int num_floor_segments=rand()%WORLD_MAX_FLOOR_SEGMENTS;
	for(int i=0; i<num_floor_segments; i++)
	{
		int location_x=rand()%(WORLD_GRID_SIZE-2)+1;
		int location_y=rand()%(WORLD_GRID_SIZE-2)+1;
		int seg_length=rand()%(WORLD_GRID_SIZE/2);
		
		//don't block exit
		if(gate_exit==PATH_GATE_BOTTOM && location_y==1)
		{
			continue;
		}

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