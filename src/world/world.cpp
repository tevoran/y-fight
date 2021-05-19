#include "y-fight.hpp"


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



