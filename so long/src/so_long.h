#ifndef SO_LONG_H
#define SO_LONG_H

#include "../mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"


#define TILE 64


#define KEY_ESC1 53
#define KEY_ESC2 65307
#define KEY_W1 13
#define KEY_W2 119
#define KEY_A1 0
#define KEY_A2 97
#define KEY_S1 1
#define KEY_S2 115
#define KEY_D1 2
#define KEY_D2 100

#define EVENT_DESTROY 17

typedef struct s_img
{
    void *img; int w; int h;
} t_img;


typedef struct s_tex
{
t_img floor; t_img wall; t_img exit_[2];
t_img player[4];
t_img coin[4];
t_img enemy[4];
} t_tex;


typedef struct s_enemy
{
    int x;
    int y;
    int dir;
} t_enemy;


typedef struct s_map {
char **grid; int rows; int cols;
int px; int py;
int collectibles;
} t_map;


typedef struct s_game
{
    void *mlx;
    void *win;
    t_map map;
    t_tex tex;
    t_enemy *enemies;
    int enemy_count;
    int moves;
    int anim_frame;
    int anim_tick;
    int hud;
} t_game;

int load_map(const char *path, t_map *out, t_enemy **enemies, int *enemy_count);
int validate_map(t_map *m, char **errmsg);
void free_map(t_map *m);

int load_textures(t_game *g);
void destroy_textures(t_game *g);
void redraw(t_game *g);

int on_key(int key, t_game *g);
int on_close(t_game *g);
int tick_anim(void *param);

void step_enemies(t_game *g);

void die(const char *msg);
void *xmalloc(size_t n);

#endif