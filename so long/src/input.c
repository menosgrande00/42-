#include "so_long.h"

static void try_move(t_game *g, int dx, int dy)
{
    int nx = g->map.px + dx;
    int ny = g->map.py + dy;
    if (nx < 0 || ny < 0 || nx >= g->map.cols || ny >= g->map.rows)
        return;
    char cell = g->map.grid[ny][nx];
    if (cell == '1')
        return;
    if (cell == 'C')
    {
        g->map.collectibles--;
        g->map.grid[ny][nx] = '0';
    }
    if (cell == 'E' && g->map.collectibles == 0)
        on_close(g);
    g->map.px = nx;
    g->map.py = ny;
    g->moves++;
    redraw(g);
}

int on_key(int key, t_game *g)
{
    if (key==KEY_ESC1 || key==KEY_ESC2)
        on_close(g);
    else if (key==KEY_W1 || key==KEY_W2)
        try_move(g, 0, -1);
    else if (key==KEY_A1 || key==KEY_A2)
        try_move(g, -1, 0);
    else if (key==KEY_S1 || key==KEY_S2)
        try_move(g, 0, 1);
    else if (key==KEY_D1 || key==KEY_D2)
        try_move(g, 1, 0);
    return 0;
}

int on_close(t_game *g)
{
    destroy_textures(g);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    free(g->enemies);
    free_map(&g->map);
    exit(0);
}
