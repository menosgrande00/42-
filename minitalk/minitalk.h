#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void	processor(int sig);
void	send_char(int pid, char c);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
int		ft_atoi(const char *str);
int		ft_isdigit(int x);

char	*ft_itoa(int n);
void	pid_client_checker(int sig);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void	*dest, const void	*src, size_t	n);

#endif
