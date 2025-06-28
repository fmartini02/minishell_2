/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:36:42 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 17:29:39 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>

/*STD FUNCTIONS START*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*checking functions*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_ispace(int c);

/*transformation functions*/
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	**ft_split(char const *s, char c);
char	*ft_utoa(unsigned long long int n, int cast_type);

/*memory functions*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

/* Length & Measurement*/
int		ft_matlen(void **s);
char	*ft_strcpy_till_(char *dest, char *src, int i, char c);
size_t	ft_strlen_till_space(char *s, int i);
size_t	ft_strlen(const char *s);
size_t	ft_word_len(char *s);
size_t	ft_skip_spaces(char *s, size_t i);
int		ft_uns_len(unsigned long n, int base, int cast_type);
int		ft_num_len(long int n, int base);

/*search and compare*/
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

/*Copy & Concatenate*/
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*Function Application*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*listes*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*printing functions*/
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(int c);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_print_mat_str(void *mat, int depth);
void	ft_print_list(t_list *lst, char cast);

/*node creation*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **plst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

/*list Measurement*/
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
/*STD FUNCTIONS END*/

/*PRINTF FUNCTION START*/
typedef struct s_flags
{
	int	num;
	int	zero;
	int	space;
	int	dot;
	int	neg;
	int	pos;
	int	sharp;
	int	done;
	int	dub;
}	t_flags;

typedef struct s_info
{
	const char			*s;
	int					i;
	int					p_b;
	unsigned long int	p_tmp;
	unsigned int		u_tmp;
	va_list				*args;
}	t_info;

/*mandatory funs*/
int		ft_printf(const char *str, ...);
void	expand_flags(t_info *info);
void	lputchar(char c, int *r);
void	lputstr(char *s, int *r);
void	lputnbr(int n, int *p_b);
void	lputunsigned(unsigned int n, int *p_b);
void	lputexa(unsigned int u, t_info *info, char c);
void	lputadrr(t_info *info);
/*bonus utils*/
void	print_width(int width, int len, t_info *info, t_flags *flags);
void	build_num(unsigned long int n, char *base, char *buf, int cast_type);
int		ft_skip_num(const char *s, int i);
void	init_info(t_info *info, const char *str, va_list *args);
int		init_flags(char c, t_flags *flags, t_info *info, int *i);
int		check_stdflags(char c);
void	ptr_case(void *ptr, t_info *info);
/*dot flag funs*/
void	put_prec_num_neg(t_flags *flags, t_info *info);
void	put_prec_uns_neg(t_flags *flags, t_info *info);
void	put_prec_num(t_flags *flags, t_info *info);
void	put_prec_uns(t_flags *flags, t_info *info);
void	handle_dot(t_flags *flags, t_info *info, char c);
void	spec_dot_neg_case(t_flags *flags, t_info *info, char c);
void	spec_dot_cases(t_flags *flags, t_info *info, char c);
void	put_dot_case(t_flags *flags, t_info *info, char c);
void	put_prec_uns(t_flags *flags, t_info *info);
void	exa_dot_width_greatest(t_flags *flags, t_info *info, char *s);
void	dot_edge_case(t_flags *flags, t_info *info,
			unsigned long int arg, char c);
void	boh(char c, char *s, unsigned int arg);
/*width flag funs*/
void	neg_case(t_info *info, char c, t_flags *flags);
void	handle_num(t_info *info, char c, t_flags *flags);
void	num_neg_int_case(t_info *info, t_flags *flags);
void	num_neg_uns_case(t_info *info, t_flags *flags);
void	num_neg_exa_case(t_info *info, t_flags *flags, char c);
void	num_neg_char_case(t_info *info, t_flags *flags);
void	num_neg_str_case(t_info *info, t_flags *flags);
void	num_neg_ptr_case(t_info *info, t_flags *flags);
void	num_char_case(t_info *info, t_flags *flags);
void	num_str_case(t_info *info, t_flags *flags);
void	num_ptr_case(t_info *info, t_flags *flags);
void	num_int_case(t_info *info, t_flags *flags);
void	num_uns_case(t_info *info, t_flags *flags);
void	num_exa_case(t_info *info, t_flags *flags, char c);
/*zero flag funs*/
void	neg_zero_case(t_flags *flags, t_info *info, char c);
void	zero_case(t_flags *flags, t_info *info, char c);
void	handle_zero(t_flags *flags, t_info *info, char c);
void	neg_zero_char_case(t_flags *flags, t_info *info);
void	neg_zero_str_case(t_flags *flags, t_info *info);
void	neg_zero_ptr_case(t_flags *flags, t_info *info);
void	neg_zero_int_case(t_flags *flags, t_info *info);
void	neg_zero_uns_case(t_flags *flags, t_info *info);
void	neg_zero_exa_case(t_flags *flags, t_info *info, char c);
void	zero_char_case(t_flags *flags, t_info *info);
void	zero_str_case(t_flags *flags, t_info *info);
void	zero_ptr_case(t_flags *flags, t_info *info);
void	zero_int_case(t_flags *flags, t_info *info);
void	zero_uns_case(t_flags *flags, t_info *info);
void	zero_exa_case(t_flags *flags, t_info *info, char c);
/*space flag funs*/
void	handle_space(t_info *info, t_flags *flags, char c);
void	space_char(int c, t_info *info, t_flags *flags);
void	space_str(char *s, t_info *info, t_flags *flags);
void	space_adrr(void *p, t_info *info, t_flags *flags);
void	space_hexa(unsigned int n, t_info *info, t_flags *flags, char c);
void	space_uns(unsigned int n, t_info *info, t_flags *flags);
void	space_int(int n, t_info *info, t_flags *flags);
/*sharp flag funs*/
void	handle_sharp(t_info *info, char c, t_flags *flags);
/*pos flag funs*/
void	handle_pos(t_flags *flag, t_info *info, char c);
void	pos_char_case(t_flags *flag, t_info *info);
void	pos_str_case(t_flags *flag, t_info *info);
void	pos_ptr_case(t_flags *flags, t_info *info);
void	pos_int_case(t_flags *flags, t_info *info);
void	pos_uns_case(t_flags *flags, t_info *info);
void	pos_hexa_case(t_flags *flags, t_info *info, char c);
void	neg_pos_char_case(t_flags *flag, t_info *info);
void	neg_pos_str_case(t_flags *flag, t_info *info);
void	neg_pos_ptr_case(t_flags *flags, t_info *info);
void	neg_pos_int_case(t_flags *flags, t_info *info);
void	neg_pos_hexa_case(t_flags *flags, t_info *info, char c);
void	neg_pos_uns_case(t_flags *flags, t_info *info);
/*PRINTF FUNCTIONS END*/

/*GNL FUNCTIONS START*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
/*GNL FUNCTIONS END*/

#endif
