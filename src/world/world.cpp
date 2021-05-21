#include "y-fight.hpp"


void yf::world::render()
{
	//leftern most tile row
	int tile_row_start_x=m_camera->x/TILE_SIZE_X;
	if(tile_row_start_x<0)
	{
		tile_row_start_x=0;
	}

	//most right tile row
	int tile_row_end_x=(m_camera->x+m_game->resx)/TILE_SIZE_X+1;
	if(tile_row_end_x>=WORLD_SIZE_X)
	{
		tile_row_end_x=WORLD_SIZE_X-1;
	}


	for(int iy=0; iy<WORLD_SIZE_Y; iy++)
	{
		if(	((m_game->resy-(iy-1)*TILE_SIZE_Y)-m_camera->y)>0 && 
			((m_game->resy-iy*TILE_SIZE_Y)-m_camera->y)<m_game->resy)
		{
			for(int ix=tile_row_start_x; ix<tile_row_end_x; ix++)
			{
				world_tileset[0].render(world_filling[ix][iy], ix*TILE_SIZE_X, iy*TILE_SIZE_Y);
			}			
		}

	}
}



