/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:43:02 by ebucheit          #+#    #+#             */
/*   Updated: 2016/10/03 14:46:40 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_end(const char *s, int start)
{
	int end;

	end = 0;
	while (s[end] != '\0')
		end++;
	while (s[end] <= ' ' && end > start)
		end--;
	return (end);
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	while (s[start] <= ' ' && s[start] != '\0')
		start++;
	end = find_end(s, start);
	if (!(new = ft_strnew((end - start) + 1)))
		return (NULL);
	while (start <= end)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
