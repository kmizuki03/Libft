/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:58:36 by kato              #+#    #+#             */
/*   Updated: 2025/04/24 18:29:18 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*word_dup(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_word(char **words, size_t index)
{
	while (index > 0)
	{
		free(words[index - 1]);
		index--;
	}
	free(words);
}

static int	ft_split_main_loop(char **result, const char *s, char c,
		size_t word)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < word)
	{
		while (*s == c && *s != '\0')
			s++;
		j = 0;
		while (s[j] != c && s[j] != '\0')
			j++;
		result[i] = word_dup(s, j);
		if (result[i] == NULL)
		{
			free_word(result, i);
			return (0);
		}
		s += j;
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word;

	if (s == NULL)
		return (NULL);
	word = count_words(s, c);
	result = malloc((word + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (!ft_split_main_loop(result, s, c, word))
		return (NULL);
	return (result);
}
