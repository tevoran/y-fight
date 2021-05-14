#include "y-fight.hpp"


int main()
{
	yf::game game("Y-FIGHT");
	yf::object player(&game, "../assets/player.png", 16, 16, (int)(0.026*(float)game.resx), (int)(0.046*(float)game.resy));
	yf::object cursor(&game, "../assets/cursor.png", 16, 16, (int)(0.016*(float)game.resx), (int)(0.029*(float)game.resy));
	player.x=400;
	player.y=800;

	while(!game.quit)
	{
		input_handling(game, player, cursor);
		player.physics(PHYSICS_GRAVITY_FLAG);

		player.render(0);
		cursor.render(0);

		game.update(0);
	}
	return 0;
}