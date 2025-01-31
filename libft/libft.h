/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:43 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/30 17:05:11 by dasalaza         ###   ########.fr       */
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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}					t_list;

/* ************************************************************************** */
/*                          LIST                                              */
/* ************************************************************************** */

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ************************************************************************** */
/*                                 MEMORY                                     */
/* ************************************************************************** */

int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);

/* ************************************************************************** */
/*                                 MEMORY                                     */
/* ************************************************************************** */

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);

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
char			*ft_strchr(const char *s, int c);
int				ft_strchr_true(const char *s, char c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

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
int				ft_strchr_c(const char *s, char c);
char			*initial_buffer(char *storage);

/* ************************************************************************** */
/*                              MINISHELL									  */
/* ************************************************************************** */

#endif
