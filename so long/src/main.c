#include "so_long.h"

int main(int argc, char **argv)
{
    t_game g;
    char *err = NULL;
    if (argc != 2)
        die("usage: ./so_long maps/level.ber");
    ft_bzero(&g, sizeof(g));
    g.hud = 1;
    load_map(argv[1], &g.map, &g.enemies, &g.enemy_count);
    validate_map(&g.map, &err);
    g.mlx = mlx_init();
    if (!g.mlx)
        die("mlx_init failed");
    g.win = mlx_new_window(g.mlx, g.map.cols*TILE, g.map.rows*TILE, "so_long");
    if (!g.win)
        die("mlx_new_window failed");
    load_textures(&g);
    redraw(&g);
    mlx_key_hook(g.win, on_key, &g);
    mlx_hook(g.win, EVENT_DESTROY, 0, on_close, &g);
    mlx_loop_hook(g.mlx, tick_anim, &g);
    mlx_loop(g.mlx);
    return 0;
}