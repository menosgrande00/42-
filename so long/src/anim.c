#include "so_long.h"

int tick_anim(void *param)
{
    t_game *g = (t_game*)param;
    g->anim_tick++;
    if (g->anim_tick % 10 == 0)
    {
        g->anim_frame = (g->anim_frame + 1) % 32;
        step_enemies(g);
        redraw(g);
    }
    return 0;
}
