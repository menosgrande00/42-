#include "so_long.h"

int	time_map(void)
{
	static struct timeval	last_time;
	struct timeval	current_time;
	double		time_diff;
	
	gettimeofday(&current_time, NULL);
	if(last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	time_diff = (current_time.tv_sec - last_time.tv_sec)
			+(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	if (time_diff >= 0.016)
	{
		last_time = current_time;
		return (1);
	}
	return (0);
}

int time_after_time(void)
{
	static struct timeval	 animation_start;
	static struct timeval	last_time;
	struct timeval			current_time;
	double					time_diff;
	double					animation_time;
	
	animation_start.tv_sec = 0;
	animation_start.tv_usec = 0;
	gettimeofday(&current_time, NULL);
	if(last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	time_diff = (current_time.tv_sec - last_time.tv_sec) +
		(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	animation_time = fmod((current_time.tv_sec - animation_start.tv_sec) +
				(current_time.tv_usec - animation_start.tv_usec) / 1000000.0, 1.000);
	if (time_diff >= 0.016)
 		last_time = current_time;
	if (animation_time < 0.100 || (animation_time >= 0.400 && animation_time < 0.500))
        return (0);
    else if (animation_time < 0.200 || (animation_time >= 0.300 && animation_time < 0.400))
        return (1);
    else if (animation_time < 0.300)
        return (2);
    else if (animation_time < 0.600 || (animation_time >= 0.900 && animation_time < 1.000))
        return (3);
    else if (animation_time < 0.700 || (animation_time >= 0.800 && animation_time < 0.900))
        return (4);
    else if (animation_time < 0.800)
        return (5);
    return (0);
}

int	time_for_enemy(void)
{
	static struct timeval	animation_start;
	static struct timeval	last_time;
	struct timeval			current_time;
	double					time_diff;
	double					animation_time;

	animation_start.tv_sec = 0;
	animation_start.tv_usec = 0;
	gettimeofday(&current_time, NULL);
	if(last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	time_diff = (current_time.tv_sec - last_time.tv_sec) +
		(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	animation_time = fmod((current_time.tv_sec - animation_start.tv_sec) +
				(current_time.tv_usec - animation_start.tv_usec) / 1000000.0, 1.000);
	if (time_diff >= 0.016)
 		last_time = current_time;
	if (animation_time < 0.100 || (animation_time >= 0.400 && animation_time < 0.500))
		return (0);
	else if (animation_time < 0.200 || (animation_time >= 0.300 && animation_time < 0.400))
		return (1);
	else if (animation_time < 0.300)
		return (2);
	else if (animation_time < 0.600 || (animation_time >= 0.900 && animation_time < 1.000))
		return (3);
	else if (animation_time < 0.700 || (animation_time >= 0.800 && animation_time < 0.900))
		return (4);
	else if (animation_time < 0.800)
		return (5);
	return (0);
}

int	time_for_attack(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	static int				frame;
	double					time_diff;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
	{
		last_time = current_time;
		return (frame);
	}
	time_diff = (current_time.tv_sec - last_time.tv_sec) +
		(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	if (time_diff >= 0.03)
	{
		frame = (frame + 1) % 3;
		last_time = current_time;
	}
	return (frame);
}
