#include "so_long.h"

static void put(t_game *g, t_img img, int x, int y)
{
    mlx_put_image_to_window(g->mlx, g->win, img.img, x*TILE, y*TILE);
}

static void draw_hud(t_game *g)
{
    if (!g->hud)
        return;
    char *s = ft_itoa(g->moves);
    if (!s)
        return;
    mlx_string_put(g->mlx, g->win, 16, 20, 0xFFFFFF, "Moves: ");
    mlx_string_put(g->mlx, g->win, 96, 20, 0xFFFFFF, s);
    free(s);
}

void redraw(t_game *g)
{
    int r;
    int c;
    int pf=(g->anim_frame%4);
    int cf=(g->anim_frame%4);
    int ef=(g->anim_frame/8)%2;
    int enf=(g->anim_frame%4);

    for (r=0; r<g->map.rows; ++r)
    for (c=0; c<g->map.cols; ++c)
    {
        char ch = g->map.grid[r][c];
        put(g, g->tex.floor, c, r);
        if (ch=='1')
            put(g, g->tex.wall, c, r);
        else if (ch=='C')
            put(g, g->tex.coin[cf], c, r);
        else if (ch=='E')
            put(g, g->tex.exit_[ef], c, r);
    }
    for (int i=0;i<g->enemy_count;i++)
        put(g, g->tex.enemy[enf], g->enemies[i].x, g->enemies[i].y);
    put(g, g->tex.player[pf], g->map.px, g->map.py);

    draw_hud(g);
}
