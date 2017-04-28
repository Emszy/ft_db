/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:42:28 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:42:30 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		c_w(char *s, char c)
{
	int	words;

	while (*s && *s == c)
		++s;
	words = (*s) ? 1 : 0;
	while (*s)
	{
		if (*s == c && s[1] && s[1] != c)
			++words;
		++s;
	}
	return (words);
}

static char		**place_word(const char *s, char c, char **result, char *start)
{
	while (*s)
	{
		if (*s == c)
		{
			if (start != s)
				*(result++) = ft_strsub(start, 0, s - start);
			start = (char *)s + 1;
		}
		++s;
	}
	if (start != s)
		*(result++) = ft_strsub(start, 0, s - start);
	*result = NULL;
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	int		words;
	char	*start;
	char	**result;

	words = c_w((char *)s, c);
	if (!s || !c)
		return (NULL);
	if (!(result = (char **)malloc(sizeof(char *) * (c_w((char *)s, c) + 1))))
		return (NULL);
	start = (char *)s;
	result = place_word(s, c, result, start);
	return (result - words);
}
