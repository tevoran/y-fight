#include "y-fight.hpp"


bool yf::collision(object& a, object& b)
{
	if(	a.dst_rect.x<(b.dst_rect.x+b.dst_rect.w) &&
		(a.dst_rect.x+a.dst_rect.w)>b.dst_rect.x &&
		a.dst_rect.y<(b.dst_rect.y+b.dst_rect.h) &&
		(a.dst_rect.y+a.dst_rect.h)>b.dst_rect.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool yf::collision(SDL_Rect& a, SDL_Rect& b) //returns true, if there is a collision, else false
{
	if(	a.x<(b.x+b.w) &&
		(a.x+a.w)>b.x &&
		a.y<(b.y+b.h) &&
		(a.y+a.h)>b.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}