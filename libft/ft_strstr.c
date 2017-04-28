/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:42:37 by ebucheit          #+#    #+#             */
/*   Updated: 2016/09/30 21:42:39 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	if (!(ft_strlen(little)))
		return ((char*)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (little[j] == big[i + j])
		{
			if (little[j + 1] == '\0')
			{
				return ((char*)big + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
