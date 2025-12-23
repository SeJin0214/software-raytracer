/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:49:21 by sejjeong          #+#    #+#             */
/*   Updated: 2025/12/23 17:38:12 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdbool.h>
# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
bool			is_whitespace(const char ch);
bool			has_uppercase(const char *str);
void			do_nothing(void* object);

/* memory */
inline void	*ft_memset(void *dest, int c, size_t n)
{
	char	*p;
	size_t	count;

	p = dest;
	count = 0;
	while (count++ < n)
	{
		*p++ = (char)c;
	}
	return (dest);
}

inline int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*p1;
	unsigned char	*p2;

	count = 1;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while (*p1 == *p2 && count < n)
	{
		++p1;
		++p2;
		++count;
	}
	return (*p1 - *p2);
}

void			ft_bzero(void *dest, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_atoi(const char *nptr);
int				ft_atoi_base(const char *num, const char *base);
long			ft_atol(const char *nptr);
bool			try_atoi(const char *nums, int *out_result);
bool			try_atof(char *nums, float *out_result);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_realloc(void *pa, size_t current_size, \
size_t override_size);
void			clear_words(char **words);
void			clear_ints(int **ints, size_t size);

/* str */
char			*ft_strstr_or_null(const char *big, const char *little);
char			*ft_strnstr_or_null(const char *big, \
		const char *little, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s);
char			*ft_strndup_malloc(const char *src, const size_t n);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strsjoin(const char **strs, size_t n);
char			*ft_strtrim(const char *s1, const char *set);
size_t			ft_strs_len(const char **strs);
char			**ft_split(const char *s, char c);
size_t			get_count_words(const char *s, char c);
size_t			get_count_to_words(char **words);
char			**ft_split_by_quote(const char *str, const char delim);
char			*ft_itoa(int n);
char			*ft_uitoa(unsigned int n);
char			*ft_ltoa(long n);
int				indexof(const char *str, const char ch);

size_t			get_digit(long num);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

/* fd */
int				ft_putchar_fd(const char c, int fd);
int				ft_putstr_fd(const char *s, int fd);
int				ft_putendl_fd(const char *s, int fd);
int				write_uint_fd(unsigned int uint, const int fd);
int				write_int_fd(int nbr, const int fd);
int				write_number_in_buffer(const char *buffer, \
		const int fd, const size_t size);

/* linked list */
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new_node);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
		void (*del)(void *));
t_list			*ft_lst_prev_or_null(t_list *head, t_list *current);

/* math */
unsigned int	generate_hash_65599(const char *str);

void			sprint_itoa(char *dest, int num);
void			sprint_uitoa(char *dest, unsigned int num);
void			sprint_abs_toa(char *dest, int num);
int				is_zero(char *nums, int size);
void			ft_assert(bool is_condition, char *message);

/* error */
void			exit_by_error(const char *func_name, const char *message);
void			exit_by_exception(const char *func_name, const char *message);

void			swap_type(void *data1, void *data2, size_t size);
void			swap_int(int *int1, int *int2);

#endif
