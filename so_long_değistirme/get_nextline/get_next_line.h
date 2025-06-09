/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:31:18 by agurses           #+#    #+#             */
/*   Updated: 2024/12/27 16:36:09 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*ft_read(int fd, char *buffer);
char	*ft_strchr(const char *str, char str2);
char	*get_next_line(int fd);
char	*ft_strjoin(char *str1, char *str2);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
