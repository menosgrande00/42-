#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_cfg	cfg;

	if (argc == 2)
	{
		if (set_tex_color_lines(&cfg, argv[1]))
		{
			free_cfg(&cfg);
			return (1);
		}
	}
	else
		strerror("Program takes just a 2 arguman!");
	return (0);
}
