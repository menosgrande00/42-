#ifndef MINITALK_H
# define MINITALK_H

#include "signal.h"
#include "ft_printf/ft_printf.h"

int ft_atoi(const char *str);
void ascii_to_byte(int pid, char c);
void convert(int sig);

#endif