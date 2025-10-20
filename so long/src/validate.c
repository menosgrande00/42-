#include "so_long.h"

static int valid_char(char ch)
{
    return (ch=='0'||ch=='1'||ch=='C'||ch=='E'||ch=='P');
}

int validate_map(t_map *m, char **errmsg)
{
    (void)errmsg;
    int r;
    int c;
    int exits=0, players=0, coins=0;
    if (m->rows < 3 || m->cols < 3)
        die("map too small");
    for (c=0;c<m->cols;c++)
        if (m->grid[0][c] != '1' || m->grid[m->rows-1][c] != '1')
            die("map not closed (top/bottom)");
    for (r=0;r<m->rows;r++)
        if (m->grid[r][0] != '1' || m->grid[r][m->cols-1] != '1')
            die("map not closed (sides)");

    for (r=0;r<m->rows;r++) for (c=0;c<m->cols;c++)
    {
        char ch = m->grid[r][c];
        if (!valid_char(ch)) die("invalid character in map");
        if (ch=='E') exits++;
        if (ch=='C') coins++;
        if (ch=='P') { players++; m->px=c; m->py=r; }
    }
    if (exits < 1 || coins < 1 || players != 1)
        die("map must have 1 P, >=1 C, >=1 E");
    m->collectibles = coins;
    return 1;
}
