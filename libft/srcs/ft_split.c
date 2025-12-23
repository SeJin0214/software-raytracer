/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:33:22 by sejjeong          #+#    #+#             */
/*   Updated: 2025/12/23 23:22:52 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	get_length_word(const char *s, char c);

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		i;
	size_t	word_len;

	res = ft_calloc(sizeof(char *), get_count_words(s, c) + 1);
	i = 0;
	while (*s != '\0' && res != NULL)
	{
		word_len = get_length_word(s, c);
		if (word_len == 0)
		{
			++s;
			continue ;
		}
		res[i] = malloc(sizeof(char) * (word_len + 1));
		if (res[i] == NULL)
		{
			clear_words(res);
			return (NULL);
		}
		ft_strlcpy(res[i++], s, word_len + 1);
		s += word_len;
	}
	return (res);
}

size_t	get_count_words(const char *s, char c)
{
	size_t	count;
	int		is_repeated;

	count = 0;
	is_repeated = TRUE;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (is_repeated == FALSE)
				++count;
			is_repeated = TRUE;
		}
		else
			is_repeated = FALSE;
		++s;
	}
	if (is_repeated == FALSE)
		++count;
	return (count);
}

static size_t	get_length_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		++s;
		++count;
	}
	return (count);
}

void	clear_words(char **words)
{
	char	**pp;

	if (words == NULL)
	{
		return ;
	}
	pp = words;
	while (*pp != NULL)
	{
		free(*pp);
		*pp = NULL;
		++pp;
	}
	free(words);
	words = NULL;
}

size_t	get_count_to_words(const char **words)
{
	size_t	i;

	i = 0;
	while (words[i] != NULL)
	{
		++i;
	}
	return (i);
}
