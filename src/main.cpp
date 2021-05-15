#include "y-fight.hpp"

#undef main

int main(int argc, char *argv[])
{
	yf::game game("Y-FIGHT");
	yf::camera camera(0.2, game.resx, game.resy, (int)(0.046*(float)game.resy));
	yf::world world(&game, &camera, "../assets/tileset.png");
	yf::object player(&game, &camera, "../assets/player.png", 16, 16, (int)(0.052*(float)game.resx), (int)(0.096*(float)game.resy));
	yf::object cursor(&game, &camera, "../assets/cursor.png", 16, 16, (int)(0.016*(float)game.resx), (int)(0.029*(float)game.resy));
	player.x=400;
	player.y=800;

	while(!game.quit)
	{
		world.interact(player);

		input_handling(game, camera, player, cursor);
		
		player.physics(PHYSICS_GRAVITY_FLAG);
		
		camera.update(game.dt, player.x, player.y);

		world.render();
		player.render(0);

		cursor.render(0);

		game.update(true, 60, camera);
	}
	return 0;
}