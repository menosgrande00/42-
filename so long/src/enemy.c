#include "so_long.h"

static int blocked(t_game *g, int x, int y)
{
    char ch = g->map.grid[y][x];
    return (ch=='1' || ch=='E');
}

void step_enemies(t_game *g)
{
    for (int i=0;i<g->enemy_count;i++)
    {
        t_enemy *e = &g->enemies[i];
        int nx = e->x + e->dir, ny = e->y;
        if (nx <= 0 || nx >= g->map.cols-1 || blocked(g, nx, ny))
            e->dir = -e->dir;
        else
            e->x = nx;
        if (e->x == g->map.px && e->y == g->map.py)
            on_close(g);
    }
}
