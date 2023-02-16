/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:55:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 16:33:49 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>

int			ft_isalnum(char c);
int			ft_isalpha(char c);
int			ft_isascii(char c);
int			ft_ischarset(char c, const char *set);
int			ft_isdigit(char c);
int			ft_isline(char *str);
int			ft_isprint(char c);
int			ft_isspace(int c);
int			ft_isint(char *str);
int			ft_is_samesign(int a, int b);

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);

int			ft_putchar_fd(int c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putunbr_fd(unsigned int n, int fd);
int			ft_putuhexnbr_fd(size_t n, int fd, char cs);

char		**ft_split(const char *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strlcat(char *dest, const char *src, int n);
int			ft_strlcpy(char *dest, const char *src, int n);
int			ft_strlen(const char *str);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(const char *s, int start, int len);
char		*ft_strcat(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_count_chars(char *str, char c);
int			ft_chars_valid(char *str, char *valid_chars);
int			ft_strfind(char *str, char c);
int			ft_endwrd(char *str, int i);

int			ft_abs(int n);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_digitcount(unsigned long n, int base);
int			ft_max(int a, int b);

void		ft_exit_w_error(char *str);

int			ft_ext_ok(char *filename, char *ext);

#endif
