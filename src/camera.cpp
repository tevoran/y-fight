#include "y-fight.hpp"

#define CAMERA_FPS 150

yf::camera::camera(float delay, int resx, int resy, int player_height)
{
	m_resx=resx;
	m_resy=resy;
	m_player_height=player_height;

	num_delayed_frames=(float)CAMERA_FPS*delay;
	std::cout << "delayed camera frames: " << num_delayed_frames << std::endl;
	past_frame_x=new float[num_delayed_frames];
	past_frame_y=new float[num_delayed_frames];

	//zero is frame that is read first
	//new entries are getting to the end
	for(int i=0; i<num_delayed_frames; i++)
	{
		past_frame_x[i]=0;
		past_frame_y[i]=0;
	}
}

yf::camera::~camera()
{
	delete [] past_frame_x;
	delete [] past_frame_y;
}

void yf::camera::update(float frame_dt, float player_x, float player_y)
{
	camera_new_frame_cooldown-=frame_dt;
	if(camera_new_frame_cooldown<=0)
	{
		//zero is frame that is read first
		//new entries are getting to the end
		x=past_frame_x[0];
		y=past_frame_y[0];


		for(int i=1; i<num_delayed_frames; i++)
		{
			past_frame_x[i-1]=past_frame_x[i];
			past_frame_y[i-1]=past_frame_y[i];
		}

		past_frame_x[num_delayed_frames-1]=player_x-m_resx/2;
		past_frame_y[num_delayed_frames-1]=-player_y+m_player_height;
		//std::cout << past_frame_x[i-1] << "x" << past_frame_y[i-1] << std::endl;

		camera_new_frame_cooldown=(float)1/(float)CAMERA_FPS;
	}
}