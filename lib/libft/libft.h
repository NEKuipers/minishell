/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:04:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/07 14:29:22 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1000
# endif
# ifndef FD_SIZE
#  define FD_SIZE	1000
# endif
# ifndef CONV_LIST
#  define CONV_LIST "cspdiuxX%"
# endif

typedef struct		s_print
{
	va_list			ap;
	char			*form;
	u_int32_t		len;
	int				width;
	int				prec;
	char			pad;
	char			left;
	char			conv;
	int				out;
}					t_print;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_flags
{
	int				width;
	int				precision;
	int				leftj;
	char			sign;
	int				signornot;
	int				zero;
	int				hash;
	char			length;
	int				nbrlen;
}					t_flags;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_nbrlen(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(int fd, char **line);

int					parse_spec(char **start, t_flags *flags,
					va_list list, int *rv);
void				parse_flags(char **start, t_flags *flags);
void				parse_hub(char **start, t_flags *flags,
					va_list list, int *rv);
void				parse_length(char **start, t_flags *flags);
void				parse_precision(char **start, t_flags *flags, va_list list);
void				parse_width(char **start, t_flags *flags, va_list list);

/*
**	ft_printf by bmans
*/

int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);
void				ft_print_flags(t_print *print);
char				*ft_print_resize(char *str, t_print *print);
char				*ft_itoa_prec(int n, int prec);
char				*ft_itoa_base_prec(u_int64_t n, char *basedigits, int prec);
void				ft_print_char(t_print *print);
void				ft_print_string(t_print *print);
void				ft_print_ptr(t_print *print);
void				ft_print_int(t_print *print);
void				ft_print_uint(t_print *print);
void				ft_putnchar_fd(int c, size_t n, int fd);

void				prepare_hex(t_flags *flags, unsigned int *nbr);
void				prepare_int(t_flags *flags, int *nbr);
void				prepare_l_int(t_flags *flags, long int *nbr);
void				prepare_ll_int(t_flags *flags, long long int *nbr);
void				prepare_ptr(t_flags *flags, unsigned long *nbr);
void				prepare_un(t_flags *flags, unsigned int *nbr);

int					ft_nbrlen(int nbr);
int					ft_nbrlen_hex(unsigned int nbr);
int					ft_nbrlen_l(long int nbr);
int					ft_nbrlen_ll(long long int nbr);
int					ft_nbrlen_ptr(unsigned long nbr);
int					ft_nbrlen_un(unsigned int nbr);

void				ft_putchar_fd_count(char c, int fd, int *rv);
void				ft_puthex_lower_count(unsigned int nbr, int *rv);
void				ft_puthex_upper_count(unsigned int nbr, int *rv);
void				ft_putnbr_fd_count(int n, int fd, int *rv);
void				ft_putnbr_l_fd_count(long int nbr, int *rv);
void				ft_putnbr_ll_fd_count(long long int nbr, int *rv);
void				ft_putnstr_fd_count(char *s, int fd, int n, int *rv);
void				ft_putptr_lower_count(unsigned long nbr, int *rv);
void				ft_putunsigned_fd(unsigned int n, int fd, int *rv);

#endif
