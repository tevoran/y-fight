#include "y-fight.hpp"

#define TILE_GROUND 0
#define TILE_BACKGROUND 1


#define TILE_SIZE_X (int)(0.026*(float)m_game->resx)
#define TILE_SIZE_Y (int)(0.046*(float)m_game->resy)

yf::world::world(game* game, camera *camera, const char* path_to_tileset)
{
	m_game=game;
	world_tileset.push_back(object(m_game, camera, path_to_tileset, 16, 16, TILE_SIZE_X, TILE_SIZE_Y));

	//creating game world
	for(int iy=0; iy<(WORLD_SIZE_Y); iy++)
	{
		for(int ix=0; ix<WORLD_SIZE_X; ix++)
		{
			world_filling[ix][iy]=TILE_BACKGROUND;
			if(iy==1)
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
		for(int ix=0; ix<WORLD_SIZE_X; ix++)
		{
			world_tileset[0].render(world_filling[ix][iy], ix*TILE_SIZE_X, iy*TILE_SIZE_Y);
		}
	}
}