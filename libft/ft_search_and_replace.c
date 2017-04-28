/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_and_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:18:58 by ebucheit          #+#    #+#             */
/*   Updated: 2016/10/17 13:19:00 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_search_and_replace(char *str, int search, int new)
{
	int		index;
	char	*s;

	index = 0;
	s = malloc(ft_strlen(str) + 1);
	ft_strcpy(s, str);
	while (str[index] != '\0')
	{
		if (str[index] == search)
			s[index] = new;
		index++;
	}
	return (s);
}
