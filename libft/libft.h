/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:49:58 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 11:10:59 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

void				*ft_calloc(size_t count, size_t size);
int					ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, int len);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, int len);
void				*ft_memchr(const void *s, int c, int n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t len);
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);
int					ft_atoi(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

//-------ft_printf--------------------------------------------------------//
int					ft_printf(const char *format, ...);
int					numbr_len(unsigned int n, int base);
int					ft_putstr(char *str);
int					ft_putchar(char c);
int					ft_putnbr(int n);
int					print_p(void *ptr);
int					print_hex(unsigned long u, char c);
int					ft_print_u(unsigned int u);

//--------get_next_line----------------------------------------------------//
char				*ft_get_substr(char *s, int start, int end);
char				*ft_get_strjoin(char *s1, char *s2);
char				*ft_get_strcpy(char *s, const char *str, int len);
int					ft_get_strlen(char *s);
char				*ft_get_strdup(char *s);
char				*get_next_line(int fd);

#endif
