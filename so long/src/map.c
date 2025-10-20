#include "so_long.h"

static int has_ext(const char *s, const char *ext)
{
    size_t ls = ft_strlen(s);
    size_t le = ft_strlen(ext);

    if (ls < le)
        return 0;
    return (ft_strncmp(s + ls - le, ext, le) == 0);
}

static char *read_all(int fd)
{
    char buf[2048];
    ssize_t n;
    char *acc = ft_strdup("");

    if (!acc)
        die("malloc failed");
    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        char *chunk = ft_substr(buf, 0, (size_t)n);
        char *tmp = ft_strjoin(acc, chunk);
        free(chunk);
        free(acc);
        if (!tmp)
            die("malloc failed");
        acc = tmp;
    }
    if (n < 0)
        die("read failed");
    return acc;
}

static void count_rows_cols(char **lines, int *rows, int *cols)
{
    int r = 0;
    int c = lines[0] ? (int)ft_strlen(lines[0]) : 0;
    while (lines[r])
        r++;
    *rows=r;
    *cols=c;
}

int load_map(const char *path, t_map *out, t_enemy **enemies, int *enemy_count)
{
    if (!has_ext(path, ".ber")) die("map must have .ber extension");
        int fd = open(path, O_RDONLY);
    if (fd < 0) die("cannot open map file");
        char *data = read_all(fd); close(fd);
    if (!*data) die("empty map file");
        char **lines = ft_split(data, '\n'); free(data);
    if (!lines || !lines[0]) die("invalid map lines");

    int r;
    int c;
    count_rows_cols(lines, &r, &c);
    out->rows=r;
    out->cols=c;
    out->px=-1;
    out->py=-1;
    out->collectibles=0;
    out->grid = (char**)xmalloc(sizeof(char*) * r);

    *enemy_count = 0;
    *enemies = (t_enemy*)xmalloc(sizeof(t_enemy) * (r*c));

    for (int i = 0; i < r; ++i)
    {
        int len = (int)ft_strlen(lines[i]);
        if (len != c)
            die("map is not rectangular");
        out->grid[i] = ft_strdup(lines[i]); if (!out->grid[i]) die("malloc failed");
        for (int j=0;j<c;j++)
        {
            if (out->grid[i][j] == 'M')
            {
                (*enemies)[(*enemy_count)++] = (t_enemy){j,i,1};
                out->grid[i][j] = '0';
            }
        }
        free(lines[i]);
    }
    free(lines);
    return 1;
}
