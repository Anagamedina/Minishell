/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:43 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 11:30:59 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

/* ************************************************************************** */
/*                                 MEMORY                                     */
/* ************************************************************************** */

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);

/* ************************************************************************** */
/*                                  PRINT                                     */
/* ************************************************************************** */

void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

/* ************************************************************************** */
/*                                 STRING                                     */
/* ************************************************************************** */

char			**ft_split(const char *s, char c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(const char *s, unsigned int start, size_t len);

/* ************************************************************************** */
/*                                 PRINTF                                     */
/* ************************************************************************** */
int				ft_putchar(char c);
int				ft_putnbr(long n);
int				ft_print_string(char *str);
int				ft_hex(unsigned long nbr, const char str);
unsigned int	ft_unsignedint(unsigned int n);

/* ************************************************************************** */
/*                              GET_NEXT_LINE                                 */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

char			*ft_free(char **ptr);
int				ft_strchr_c(char *s, char c);
char			*initial_buffer(char *storage);

#endif
