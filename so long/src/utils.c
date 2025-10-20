#include "so_long.h"

void die(const char *msg)
{
    write(2, "Error\n", 6);
    if (msg)
        write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(1);
}

void *xmalloc(size_t n)
{
    void *p = malloc(n);
    if (!p)
        die("malloc failed");
    return p;
}

void free_map(t_map *m)
{
    if (!m || !m->grid)
        return;
    for (int i = 0; i < m->rows; ++i)
        free(m->grid[i]);
    free(m->grid); m->grid = NULL;
}
