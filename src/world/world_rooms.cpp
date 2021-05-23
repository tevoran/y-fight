#include "y-fight.hpp"

#define NUM_ROOM_TYPES 1


//choosing random kind of room
void yf::world::create_random_room( const int room_x, const int room_y)
{
	int room_type=rand()%NUM_ROOM_TYPES;

	switch(room_type)
	{
		case 0:
			//room_horizontal_traversal(room_x, room_y);
			break;
	}

}

//horizontal traversal room
void yf::world::room_horizontal_traversal(const int room_x, const int room_y, const PATH last_room)
{
	//filling with wall tiles
	//because the game takes place in caves
	for(int iy=0; iy<WORLD_GRID_SIZE; iy++)
	{
		for(int ix=0; ix<WORLD_GRID_SIZE; ix++)
		{
			world_filling[room_x*WORLD_GRID_SIZE+ix][room_y*WORLD_GRID_SIZE+iy]=TILE_BORDER_WALL;	
		}
	}	

	int look_for_entry_x=0;
	if(last_room==LEFT)
	{
		look_for_entry_x=room_x*WORLD_GRID_SIZE-2;
	}
	if(last_room==RIGHT)
	{
		look_for_entry_x=(room_x+1)*WORLD_GRID_SIZE+2;		
	}

	//look for the exit in the last room
	int y_min=0;
	int y_max=0;

	for(int iy=1; iy<(WORLD_GRID_SIZE-1); iy++)
	{
		if(	world_filling[look_for_entry_x][room_y*WORLD_GRID_SIZE+iy]==TILE_BACKGROUND &&
			world_filling[look_for_entry_x][room_y*WORLD_GRID_SIZE+iy-1]!=TILE_BACKGROUND)
		{
			y_min=room_y*WORLD_GRID_SIZE+iy;
		}

		if(	world_filling[look_for_entry_x][room_y*WORLD_GRID_SIZE+iy]==TILE_BACKGROUND &&
			world_filling[look_for_entry_x][room_y*WORLD_GRID_SIZE+iy+1]!=TILE_BACKGROUND)
		{
			y_max=room_y*WORLD_GRID_SIZE+iy;
		}
	}

	int y_entrance=0;
	int y_exit=0;
	if((y_max-y_min)>3)
	{
		y_entrance=rand()%(y_max-1-y_min)+y_min;
	}
	y_exit=y_entrance;

	for(int i=-2; i<=(WORLD_GRID_SIZE+1); i++)
	{
		//avoiding segfaults
		if((room_x*WORLD_GRID_SIZE+i)>=(WORLD_SIZE_X-2))
		{
			break;
		}
		if((room_x*WORLD_GRID_SIZE+i)<=0)
		{
			continue;
		}

		world_filling[room_x*WORLD_GRID_SIZE+i][y_entrance]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+i][y_entrance+1]=TILE_BACKGROUND;
		world_filling[room_x*WORLD_GRID_SIZE+i][y_entrance+2]=TILE_BACKGROUND;
	}
}