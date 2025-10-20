#include "so_long.h"

static void load_one(t_game *g, t_img *dst, const char *path)
{
    dst->img = mlx_xpm_file_to_image(g->mlx, (char*)path, &dst->w, &dst->h);
    if (!dst->img)
        die(path);
    if (dst->w != TILE || dst->h != TILE)
        die("xpm must match TILE size");
}

int load_textures(t_game *g)
{
    load_one(g, &g->tex.floor, "assets/floor.xpm");
    load_one(g, &g->tex.wall,  "assets/wall.xpm");
    load_one(g, &g->tex.player[0], "assets/player_0.xpm");
    load_one(g, &g->tex.player[1], "assets/player_1.xpm");
    load_one(g, &g->tex.player[2], "assets/player_2.xpm");
    load_one(g, &g->tex.player[3], "assets/player_3.xpm");
    load_one(g, &g->tex.coin[0],   "assets/coin_0.xpm");
    load_one(g, &g->tex.coin[1],   "assets/coin_1.xpm");
    load_one(g, &g->tex.coin[2],   "assets/coin_2.xpm");
    load_one(g, &g->tex.coin[3],   "assets/coin_3.xpm");
    load_one(g, &g->tex.exit_[0],  "assets/exit_0.xpm");
    load_one(g, &g->tex.exit_[1],  "assets/exit_1.xpm");
    load_one(g, &g->tex.enemy[0],  "assets/enemy_0.xpm");
    load_one(g, &g->tex.enemy[1],  "assets/enemy_1.xpm");
    load_one(g, &g->tex.enemy[2],  "assets/enemy_2.xpm");
    load_one(g, &g->tex.enemy[3],  "assets/enemy_3.xpm");
    return 1;
}

void destroy_textures(t_game *g)
{
    if (!g->mlx)
        return;
    mlx_destroy_image(g->mlx, g->tex.floor.img);
    mlx_destroy_image(g->mlx, g->tex.wall.img);
    for (int i=0; i<4; i++)
        mlx_destroy_image(g->mlx, g->tex.player[i].img);
    for (int i=0; i<4; i++)
        mlx_destroy_image(g->mlx, g->tex.coin[i].img);
    for (int i=0; i<2; i++)
        mlx_destroy_image(g->mlx, g->tex.exit_[i].img);
    for (int i=0; i<4; i++)
        mlx_destroy_image(g->mlx, g->tex.enemy[i].img);
}
