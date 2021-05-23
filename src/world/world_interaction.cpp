#include "y-fight.hpp"

void yf::world::interact(object& player)
{
	SDL_Rect world_collision;
	world_collision.w=TILE_SIZE_X;
	world_collision.h=TILE_SIZE_Y;

	int player_tile_x=(int)(player.x/TILE_SIZE_X+0.5);
	int player_tile_y=(int)(player.y/TILE_SIZE_Y+0.5);

	//collision with border walls and ground tiles
	//checking right side
	if(player_tile_x<WORLD_SIZE_X-1) //avoiding segfaults
	{
		if(	world_filling[player_tile_x+1][player_tile_y]==TILE_BORDER_WALL ||
			world_filling[player_tile_x+1][player_tile_y]==TILE_GROUND)
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
		if(	world_filling[player_tile_x-1][player_tile_y]==TILE_BORDER_WALL  ||
			world_filling[player_tile_x-1][player_tile_y]==TILE_GROUND)
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
		if(	world_filling[player_tile_x][player_tile_y+1]==TILE_BORDER_WALL ||
			world_filling[player_tile_x][player_tile_y+1]==TILE_GROUND)
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
		//border wall tiles
		if(	world_filling[player_tile_x][player_tile_y-1]==TILE_BORDER_WALL ||
			world_filling[player_tile_x][player_tile_y-1]==TILE_GROUND)
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
}